#include "Game/Game.h"
#include "Entity/Entity.h"
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

Game::Game()
{
  srand(static_cast<unsigned int>(time(nullptr)));
  // console->displayWelcomeMessage(mode);

  initializeHeroes();
  initializeCards();
  dealInitialCards();
}

/**
 * @brief Initializes the game's heroes.
 */
void Game::initializeHeroes()
{
  playerHero.InitHeroes();
  std::vector<std::shared_ptr<Hero>> retrievedHeroes = playerHero.GetHeroes();
  GameData_t playerClient;
  GameData_t playerServer;
  int randomIndex = rand() % retrievedHeroes.size();
  playerClient.hero = retrievedHeroes[randomIndex];
  playerServer.hero = retrievedHeroes[1 - randomIndex];
  playerData.emplace_back(playerClient);
  playerData.emplace_back(playerServer);
}

/**
 * @brief Initializes the game's cards.
 */
void Game::initializeCards()
{
  cardsPool.emplace_back(std::make_shared<FlametongueTotem>());
  cardsPool.emplace_back(std::make_shared<RagnarosTheFirelord>());
  cardsPool.emplace_back(std::make_shared<BloodmageThalnos>());
  cardsPool.emplace_back(std::make_shared<Brawl>());
  cardsPool.emplace_back(std::make_shared<Techies>());
}

/**
 * @brief Deals the initial set of cards to each player.
 */
void Game::dealInitialCards()
{
  for (auto &player : playerData)
  {
    for (int i = 0; i < 10; ++i)
    {
      int randomIndex = rand() % cardsPool.size();
      player.handEntities.emplace_back(cardsPool[randomIndex]);
    }
  }
}

void Game::play()
{
  std::vector<std::string> cardList;
  while (true)
  {
    console->clearConsole();
    for (auto &currentPlayerCard : playerData[CLIENT_INDEX].handEntities)
    {
      cardList.push_back(currentPlayerCard->GetDescription());
    }
    if (cardList.size() > 0)
    {
      int cardChoice = console->displayMenu(playerData[CLIENT_INDEX].hero->GetName() + "'s turn", cardList);
      activateEntitiesAndHeroAttack(CLIENT_INDEX, cardChoice);
      for (int i = 0; i < playerData[CLIENT_INDEX].stats.size(); i++)
      {
        std::cout << playerData[CLIENT_INDEX].stats[i] << std::endl;
      }
    }
    cardList.clear();
    console->waitForEnter();
    playerData[CLIENT_INDEX].stats.clear();
    std::swap(CLIENT_INDEX, SERVER_INDEX);
  }
}

void Game::removeEntitiesOnTable(uint8_t playerIndex, uint8_t entities)
{
  playerData[playerIndex].stats.push_back(playerData[playerIndex].hero->GetName() + " remove " + playerData[playerIndex].handEntities[entities]->GetDescription());
  playerData[playerIndex].tableEntities.erase(playerData[playerIndex].tableEntities.begin() + entities);
}
void Game::removeEntitiesOnHand(uint8_t playerIndex, uint8_t entities)
{
  playerData[playerIndex].handEntities.erase(playerData[playerIndex].handEntities.begin() + entities);
}
void Game::addBattleEntities(uint8_t playerIndex, uint8_t entities)
{
  playerData[playerIndex].stats.push_back(playerData[playerIndex].hero->GetName() + " activate " + playerData[playerIndex].handEntities[entities]->GetDescription());
  playerData[playerIndex].tableEntities.emplace_back(playerData[playerIndex].handEntities[entities]);
}

void Game::activateEntitiesAndHeroAttack(uint8_t playerIndex, uint8_t entityIndex)
{
  uint8_t currentPlayer = playerIndex;
  uint8_t opponentPlayer = 1 - playerIndex;
  addBattleEntities(currentPlayer, entityIndex);
  auto &entity = playerData[playerIndex].handEntities[entityIndex];
  std::shared_ptr<GameEntity> entityInstance = entity->createInstance();
  switch (entity->GetEntitiesType())
  {
  case EntityType::BRAWL:
    entityInstance->applyEffect(playerData, entityIndex, currentPlayer);
    removeEntitiesOnTable(currentPlayer, entityIndex);
    break;
  case EntityType::SHAMAN:
    entityInstance->applyEffect(playerData, entityIndex, currentPlayer);
    break;
  case EntityType::TECHIES:
    entityInstance->applyEffect(playerData, entityIndex, currentPlayer);
    break;
  case EntityType::MINION:
    entityInstance->applyEffect(playerData, entityIndex, currentPlayer);
    break;
  }
  entityInstance.reset();
  /*
    handling hero attack oppent hero.
  */
  playerData[playerIndex].hero->AttackHero(playerData[opponentPlayer].hero, playerData[playerIndex].hero->GetAttack());
  removeEntitiesOnHand(currentPlayer, entityIndex);
}