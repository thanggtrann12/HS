#include "Game/Game.h"
#include "Units/Units.h"
#include <iostream>
#include <iomanip>

Game::Game()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    console->displayWelcomeMessage(mode, host);
    initializeHeroes();
    initializeCards();
    dealInitialCards();
}

/**
 * @brief Starts and manages the gameplay.
 */
void Game::play()
{
    int currentPlayerIndex = 0;
    int opponentIndex = 1;

    while (heroes[currentPlayerIndex]->isAlive() && heroes[opponentIndex]->isAlive())
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        displayGameState(currentPlayerIndex, opponentIndex);
        playCard(currentPlayerIndex, opponentIndex);

        // Calculate and display total damage to opponent hero
        heroes[currentPlayerIndex]->attack(heroes[opponentIndex].get());
        std::cout << "Cards in battle: " << std::endl;
        for (auto it : heroes[currentPlayerIndex]->getBattleCard())
        {
            std::cout << it->getDescription() << std::endl;
        }
        // Swap players for the next turn
        std::swap(currentPlayerIndex, opponentIndex);
        // message.clear();
    }

    // Game over
    displayGameResult(currentPlayerIndex);
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
    std::cout << "Player " << (playerIndex + 1) << " draws " << drawnCard->getName() << "." << std::endl;
}

/**
 * @brief Handles the playing of a card by a player.
 * @param currentPlayerIndex The index of the current player.
 * @param opponentIndex The index of the opponent player.
 */
void Game::playCard(int currentPlayerIndex, int opponentIndex)
{
    heroes[currentPlayerIndex]->displayHand();
    int cardIndex;

    // Check if the player has any cards
    if (heroes[currentPlayerIndex]->getNumCards() <= 0)
    {
        heroes[opponentIndex]->takeDamage(heroes[currentPlayerIndex]->getAttack());
        message.push_back("Your hand is empty!! Only hero attacked!!");
        return; // Return early if the player has no cards
    }

    std::cout << "Select a card to play (0-" << (heroes[currentPlayerIndex]->getNumCards() - 1) << "): ";
    std::cin >> cardIndex;

    // Check if the cardIndex is within bounds
    if (cardIndex >= 0 && cardIndex < heroes[currentPlayerIndex]->getNumCards())
    {
        auto playedCard = heroes[currentPlayerIndex]->playCard(cardIndex);

        // Check if playedCard is not null
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
                        if (currentPlayerCard->getCardType() != CardType::SHAMAN)
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

                    for (auto &opponentPlayerCard : heroes[opponentIndex]->getBattleCard())
                    {
                        if (opponentPlayerCard->getCardType() != CardType::BRAWL)
                        {
                            if (currentPlayerCard->getAttack() >= opponentPlayerCard->getCurrentHP())
                            {
                                message.push_back("Card eliminated: ");
                                message.push_back("- " + opponentPlayerCard->getDescription());
                                if (opponentPlayerCard->getCardType() == CardType::TECHIES)
                                {
                                    int damageToHero = 3;
                                    heroes[opponentIndex]->takeDamage(damageToHero);
                                    heroes[currentPlayerIndex]->takeDamage(damageToHero);
                                    message.push_back("Techies deals " + std::to_string(damageToHero) + " damage to both heroes");
                                }
                                heroes[opponentIndex]->removeBattleCard(opponentPlayerCard);
                            }
                            else
                            {
                                opponentPlayerCard->takeDamage(currentPlayerCard->getAttack());
                                message.push_back("- After: " + opponentPlayerCard->getDescription());
                            }
                        }
                    }

                    heroes[opponentIndex]->takeDamage(currentPlayerCard->getAttack());
                }
        }
        displayBattlefield(currentPlayerIndex);
    }
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
void Game::displayGameState(int currentPlayerIndex, int opponentIndex)
{
    // Display game state in a table
    std::vector<std::string> currentPlayer;
    std::vector<std::string> opponentPlayer;

    currentPlayer.push_back(heroes[currentPlayerIndex]->getName());
    currentPlayer.push_back(std::to_string(heroes[currentPlayerIndex]->getCurrentHP()));
    currentPlayer.push_back(std::to_string(heroes[currentPlayerIndex]->getAttack()));
    currentPlayer.push_back(std::to_string(heroes[opponentIndex]->getTotalDamage()));

    opponentPlayer.push_back(heroes[opponentIndex]->getName());
    opponentPlayer.push_back(std::to_string(heroes[opponentIndex]->getCurrentHP()));
    opponentPlayer.push_back(std::to_string(heroes[opponentIndex]->getAttack()));
    opponentPlayer.push_back(std::to_string(heroes[currentPlayerIndex]->getTotalDamage()));
    console->displayGameState(currentPlayer, opponentPlayer, message);
    message.clear();
    currentPlayer.clear();
    opponentPlayer.clear();
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