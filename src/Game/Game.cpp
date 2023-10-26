#include "Game/Game.h"
#include "Units/Units.h"
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

Game::Game()
{
  turnCounts = std::vector<int>(2, 0);
  srand(static_cast<unsigned int>(time(nullptr)));
  console->displayWelcomeMessage(mode);

  initializeHeroes();
  initializeCards();
  dealInitialCards();
}

/**
 * @brief Starts and manages the gameplay.
 */
void Game::play()
{
  data_t data;
  MySocket socket(mode);
  if (mode == 1)
    console->loadingConsole();
  while (true)
  {
    data_t receivedData;
    data_t sendData;
    if (mode == 1)
    {

      sendData.choice = 0;
      sendData.mode = HAND_CARD;
      for (auto &currentPlayerCard : heroes[clientIndex]->getHandCards())
      {
        sendData.clientHandCards.push_back(currentPlayerCard->getDescription());
      }
      socket.sendData(sendData);
      socket.receiveData(receivedData);

      console->clearConsole();

      playCard(clientIndex, serverIndex, static_cast<int>(receivedData.choice));
      sendData.choice = 0;
      sendData.mode = BATTTLE_STATS;
      getGameStats(sendData);
      socket.sendData(sendData);
      std::vector<std::string> menuList;
      for (auto &currentPlayerCard : heroes[serverIndex]->getHandCards())
      {
        menuList.push_back(currentPlayerCard->getDescription());
      }
      console->displayGameState(sendData.clientHeroStats, sendData.serverHeroStats, sendData.gameInfos);
      calculatePlayerTurnCount();
      int choice = console->displayMenu("Choose an option (" + std::to_string(menuList.size()) + " options)", menuList);

      menuList.clear();
      console->clearConsole();
      playCard(serverIndex, clientIndex, choice);
      sendData.choice = 0;
      sendData.mode = BATTTLE_STATS;
      getGameStats(sendData);
      socket.sendData(sendData);
      console->displayGameState(sendData.serverHeroStats, sendData.clientHeroStats, sendData.gameInfos);
    }
    else
    {
      socket.receiveData(receivedData);
      if (receivedData.mode == HAND_CARD)
      {
        int choice = console->displayMenu("Choose an option (" + std::to_string(receivedData.clientHandCards.size()) + " options)", receivedData.clientHandCards);
        sendData.choice = choice;
        sendData.mode = PLAY_CARD;
        socket.sendData(sendData);
      }
      if (receivedData.mode == BATTTLE_STATS)
      {
        console->displayGameState(receivedData.clientHeroStats, receivedData.serverHeroStats, receivedData.gameInfos);
      }
    }
  }
}

/**
 * @brief Initializes the game's heroes.
 */
void Game::initializeHeroes()
{
  heroes.push_back(std::make_shared<Hero>("Butcher", 120, 6));
  heroes.push_back(std::make_shared<Hero>("Slark", 72, 10));
}

/**
 * @brief Initializes the game's cards.
 */
void Game::initializeCards()
{
  cards.push_back(std::make_shared<Minion>("Ragnaros the Firelord", 1, 3, CardType::MINION));
  cards.push_back(std::make_shared<Minion>("Bloodmage Thalnos", 1, 1, CardType::MINION));
  cards.push_back(std::make_shared<FlametongueTotem>());
  cards.push_back(std::make_shared<Brawl>());
  cards.push_back(std::make_shared<Minion>("Techies", 2, 1, CardType::TECHIES));
}

/**
 * @brief Deals the initial set of cards to each player.
 */
void Game::dealInitialCards()
{
  for (auto &hero : heroes)
  {
    for (int i = 0; i < 10; ++i)
    {
      hero->addCard(drawRandomCard());
    }
  }
}

/**
 * @brief Draws a random card from the available cards.
 * @return A shared pointer to the drawn card.
 */
std::shared_ptr<Minion> Game::drawRandomCard()
{
  int randomIndex = rand() % cards.size();
  return cards[randomIndex];
}

/**
 * @brief Draws a card for a player and adds it to their hand.
 * @param playerIndex The index of the player drawing the card.
 */
void Game::drawCard(int playerIndex)
{
  auto drawnCard = drawRandomCard();
  heroes[playerIndex]->addCard(drawnCard);
  std::cout << heroes[playerIndex]->getName() << " draws " << drawnCard->getName() << "." << std::endl;
}

/**
 * @brief Handles the playing of a card by a player.
 * @param currentPlayerIndex The index of the current player.
 * @param opponentIndex The index of the opponent player.
 */
void Game::playCard(int currentPlayerIndex, int opponentIndex, int cardChoice)
{

  auto playedCard = heroes[currentPlayerIndex]->playCard(cardChoice);
  heroes[currentPlayerIndex]->attack(heroes[opponentIndex].get());

  message.push_back("Active: " + playedCard->getDescription());
  if (playedCard)
  {
    message.push_back("Active: ");
    message.push_back("- " + playedCard->getDescription());
    displayBattlefield(opponentIndex);
    if (playedCard->getCardType() == CardType::BRAWL)
    {
      if (resolveBrawl(opponentIndex))
      {
        heroes[currentPlayerIndex]->removeBattleCard(playedCard);
      }
      else
      {
        message.push_back("Brawl still on battlefield");
      }
    }
    else if (auto totem = std::dynamic_pointer_cast<FlametongueTotem>(playedCard))
    {
      if (!totem->isActivated() && heroes[currentPlayerIndex]->getBattleCard().size() > 0)
      {
        for (auto &currentPlayerCard : heroes[currentPlayerIndex]->getBattleCard())
        {
          if (currentPlayerCard->getCardType() != CardType::SHAMAN && currentPlayerCard->getCardType() != CardType::BRAWL)
          {
            message.push_back("Flametongue Totem activated, apply bonus");
            totem->applyBuff(heroes[currentPlayerIndex]->getBattleCard());
          }
        }
        totem->setActivated(true);
      }
    }
    else
      for (auto &currentPlayerCard : heroes[currentPlayerIndex]->getBattleCard())
      {

        std::vector<std::shared_ptr<Minion>> cardsToRemove;
        int shamanCount = 0;
        for (auto &opponentPlayerCard : heroes[opponentIndex]->getBattleCard())
        {
          if (opponentPlayerCard->getCardType() != CardType::BRAWL)
          {
            if (currentPlayerCard->getAttack() >= opponentPlayerCard->getCurrentHP())
            {

              if (opponentPlayerCard->getCardType() == CardType::TECHIES)
              {
                int damageToHero = 3;
                heroes[opponentIndex]->takeDamage(damageToHero);
                heroes[currentPlayerIndex]->takeDamage(damageToHero);
                message.push_back("Techies deals " + std::to_string(damageToHero) + " damage to both heroes");
              }
              if (opponentPlayerCard->getCardType() == CardType::SHAMAN)
              {
                shamanCount++;
              }
              cardsToRemove.push_back(opponentPlayerCard);
            }
            else
            {
              opponentPlayerCard->takeDamage(currentPlayerCard->getAttack());
              message.push_back("- Card " + opponentPlayerCard->getName() + "HP left: " + std::to_string(opponentPlayerCard->getCurrentHP()));
            }
          }
        }
        for (auto &opponentPlayerCard : heroes[opponentIndex]->getBattleCard())
        {
          opponentPlayerCard->setAttack(shamanCount);
        }
        if (cardsToRemove.size() > 0)
        {
          message.push_back("Card eliminated: ");
          for (auto &card : cardsToRemove)
          {
            message.push_back("- " + card->getDescription());
            heroes[opponentIndex]->removeBattleCard(card);
          }
        }
        heroes[opponentIndex]->takeDamage(currentPlayerCard->getAttack());
      }
  }
  displayBattlefield(currentPlayerIndex);
}

/**
 * @brief Resolves the effects of a brawl card played by the opponent.
 * @param opponentIndex The index of the opponent player.
 * @return True if a non-brawl card was destroyed, false otherwise.
 */
bool Game::resolveBrawl(int opponentIndex)
{
  auto &opponentMinions = heroes[opponentIndex]->getBattleCard();
  if (opponentMinions.size() > 0)
  {
    bool nonBrawlCardFound = false;
    for (int i = 0; i < opponentMinions.size(); i++)
    {
      int randomIndex = rand() % opponentMinions.size();
      std::shared_ptr<Minion> destroyedMinion = opponentMinions[randomIndex];

      if (destroyedMinion->getCardType() != CardType::BRAWL)
      {
        message.push_back("Brawl is resolved!");
        message.push_back("Player " + heroes[opponentIndex]->getName() + "'s " + destroyedMinion->getName() + " is destroyed!");

        if (destroyedMinion->getCardType() == CardType::TECHIES)
        {
          int damageToHero = 3;
          heroes[opponentIndex]->takeDamage(damageToHero);
          heroes[1 - opponentIndex]->takeDamage(damageToHero);
          message.push_back("Techies deals " + std::to_string(damageToHero) + " damage to both heroes");
        }

        opponentMinions.erase(opponentMinions.begin() + randomIndex);
        nonBrawlCardFound = true;
        break;
      }
    }

    if (!nonBrawlCardFound)
    {
      message.push_back("All cards in Player " + heroes[opponentIndex]->getName() + "'s BattleCard are brawls.");
    }

    return nonBrawlCardFound;
  }
  else
  {
    message.push_back("Player " + heroes[opponentIndex]->getName() + " has no minions to destroy.");
    return false;
  }
}

/**
 * @brief Displays the current game state.
 * @param currentPlayerIndex The index of the current player.
 * @param opponentIndex The index of the opponent player.
 */
void Game::getGameStats(data_t &data)
{
  data.gameInfos.clear();
  data.clientHandCards.clear();
  data.serverHeroStats.clear();
  data.clientHeroStats.push_back(heroes[clientIndex]->getName());
  data.clientHeroStats.push_back(std::to_string(heroes[clientIndex]->getCurrentHP()));
  data.clientHeroStats.push_back(std::to_string(heroes[clientIndex]->getAttack()));
  data.clientHeroStats.push_back(std::to_string(heroes[serverIndex]->getTotalDamage()));

  data.serverHeroStats.push_back(heroes[serverIndex]->getName());
  data.serverHeroStats.push_back(std::to_string(heroes[serverIndex]->getCurrentHP()));
  data.serverHeroStats.push_back(std::to_string(heroes[serverIndex]->getAttack()));
  data.serverHeroStats.push_back(std::to_string(heroes[clientIndex]->getTotalDamage()));
  data.gameInfos = message;
  message.clear();
}

/**
 * @brief Displays the result of the game.
 * @param winnerIndex The index of the winning player.
 */
void Game::displayGameResult(int winnerIndex)
{
  std::cout << "Player " << (winnerIndex + 1) << " wins!" << std::endl;
  std::cout << heroes[winnerIndex]->getDescription() << std::endl;
}

/**
 * @brief Displays the battlefield and cards in play for a player.
 * @param currentPlayerIndex The index of the current player.
 */
void Game::displayBattlefield(int currentPlayerIndex)
{
  message.push_back("Player: " + heroes[currentPlayerIndex]->getName());
  message.push_back("On battlefield:");
  if (heroes[currentPlayerIndex]->getBattleCard().empty())
  {
    message.push_back("Empty");
  }
  else
  {
    for (auto &currentPlayerCard : heroes[currentPlayerIndex]->getBattleCard())
    {
      message.push_back("- " + currentPlayerCard->getDescription());
    }
  }
}

bool Game::calculatePlayerTurnCount()
{
  for (int playerIndex = 0; playerIndex < 2; playerIndex++)
  {
    if (turnCounts[playerIndex] == 2)
    {
      message.push_back(heroes[playerIndex]->getName() + " draw 2 cards!");
      for (int i = 0; i < 2; i++)
      {
        drawCard(playerIndex);
      }
      turnCounts[playerIndex] = 0;
    }
    else
    {
      turnCounts[playerIndex]++;
    }
  }
}