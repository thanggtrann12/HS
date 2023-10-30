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
  playerData.push_back(playerClient);
  playerData.push_back(playerServer);
}

/**
 * @brief Initializes the game's cards.
 */
void Game::initializeCards()
{
  std::shared_ptr<Minion> minion = std::make_shared<FlametongueTotem>();

  cardsPool.push_back(std::make_shared<FlametongueTotem>());
  cardsPool.push_back(std::make_shared<RagnarosTheFirelord>());
  cardsPool.push_back(std::make_shared<BloodmageThalnos>());
  cardsPool.push_back(std::make_shared<Brawl>());
  cardsPool.push_back(std::make_shared<Techies>());
}

void Game::dealInitialCards()
{
  for (auto &player : playerData)
  {
    for (int i = 0; i < 10; ++i)
    {
      int randomIndex = rand() % cardsPool.size();
      std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(cardsPool[randomIndex]);
      if (minion)
      {
        player.handEntities.push_back(minion);
      }
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
      currentPlayerCard->SetIsUsed(false);
      cardList.push_back(currentPlayerCard->GetDescription());
    }
    if (cardList.size() > 0)
    {
      if (playerData[CLIENT_INDEX].hero->IsAlive())
      {
        int cardChoice = console->displayMenu(playerData[CLIENT_INDEX].hero->GetName() + "'s HP [" + std::to_string(playerData[CLIENT_INDEX].hero->GetHealth()) + "] turn with round [" + std::to_string(playerData[CLIENT_INDEX].turnCount + 1) + "]", cardList);
        playerData[CLIENT_INDEX].turnCount++;
        addEntityToTable(CLIENT_INDEX, cardChoice);
        removeEntityFromHand(CLIENT_INDEX, cardChoice);
        activateEntity(CLIENT_INDEX);
        cardList.clear();
      }
      else
      {
        console->clearConsole();
        std::cout << "Player Winner: " + playerData[SERVER_INDEX].hero->GetDescription() << std::endl;
        console->waitForEnter();
      }
    }
    console->waitForEnter();
    playerData[CLIENT_INDEX].stats.clear();
    playerData[SERVER_INDEX].stats.clear();
    std::swap(CLIENT_INDEX, SERVER_INDEX);
  }
}

void Game::removeEntityFromTable(int playerIndex, int entityIndex)
{
  if (entityIndex < playerData[playerIndex].tableEntities.size())
  {
    playerData[playerIndex].stats.push_back(playerData[playerIndex].hero->GetName() + " remove " + playerData[playerIndex].tableEntities[entityIndex]->GetDescription());
    playerData[playerIndex].tableEntities.erase(playerData[playerIndex].tableEntities.begin() + entityIndex);
  }
}

void Game::removeEntityFromHand(int playerIndex, int entityIndex)
{
  if (playerIndex < playerData.size())
  {
    if (!playerData[playerIndex].handEntities.empty() && entityIndex < playerData[playerIndex].handEntities.size())
    {
      playerData[playerIndex].handEntities.erase(playerData[playerIndex].handEntities.begin() + entityIndex);
    }
    else
    {
      std::cout << "Invalid entityIndex or empty hand." << std::endl;
    }
  }
  else
  {
    std::cout << "Invalid playerIndex." << std::endl;
  }
}

void Game::addEntityToTable(int playerIndex, int entityIndex)
{
  if (entityIndex < playerData[playerIndex].handEntities.size())
  {
    std::shared_ptr<GameEntity> originalEntity = playerData[playerIndex].handEntities[entityIndex];

    if (!originalEntity)
    {
      std::cout << "Invalid entity type." << std::endl;
      return;
    }

    std::shared_ptr<Minion> newEntity;

    if (originalEntity->GetEntitiesType() == EntityType::SHAMAN)
    {
      auto shamanEntity = std::dynamic_pointer_cast<FlametongueTotem>(originalEntity);
      if (shamanEntity)
      {
        newEntity = std::make_shared<FlametongueTotem>(*shamanEntity);
      }
    }
    else if (originalEntity->GetEntitiesType() == EntityType::MINION)
    {
      if (strcmp(originalEntity->GetName().c_str(), "Ragnaros the Firelord") == 0)
      {
        auto minionEntity = std::dynamic_pointer_cast<RagnarosTheFirelord>(originalEntity);
        if (minionEntity)
        {
          newEntity = std::make_shared<RagnarosTheFirelord>(*minionEntity);
        }
      }
      else
      {
        auto bloodmageEntity = std::dynamic_pointer_cast<BloodmageThalnos>(originalEntity);
        if (bloodmageEntity)
        {
          newEntity = std::make_shared<BloodmageThalnos>(*bloodmageEntity);
        }
      }
    }
    else if (originalEntity->GetEntitiesType() == EntityType::TECHIES)
    {
      auto techiesEntity = std::dynamic_pointer_cast<Techies>(originalEntity);
      if (techiesEntity)
      {
        newEntity = std::make_shared<Techies>(*techiesEntity);
      }
    }
    else if (originalEntity->GetEntitiesType() == EntityType::BRAWL)
    {
      auto brawlEntity = std::dynamic_pointer_cast<Brawl>(originalEntity);
      if (brawlEntity)
      {
        newEntity = std::make_shared<Brawl>(*brawlEntity);
      }
    }
    else
    {
      std::cout << "Invalid entity type." << std::endl;
      return;
    }

    if (newEntity)
    {
      newEntity->SetIsUsed(false);
      playerData[playerIndex].tableEntities.push_back(newEntity);
      playerData[playerIndex].stats.push_back(playerData[playerIndex].hero->GetName() + " activate " + newEntity->GetDescription());
    }
  }
}

void Game::activateEntity(int playerIndex)
{
  int totalMinionsDamage = 0;
  std::vector<std::string> tableEntitiesPlayer1;
  std::vector<std::string> tableEntitiesPlayer2;
  if (!playerData[playerIndex].tableEntities.empty())
  {
    tableEntitiesPlayer1.push_back("Active: ");
    for (size_t entityIndex = 0; entityIndex < playerData[playerIndex].tableEntities.size(); ++entityIndex)
    {
      std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(playerData[playerIndex].tableEntities[entityIndex]);
      tableEntitiesPlayer1.push_back(" - " + minion->GetDescription());
    }

    for (size_t entityIndex = 0; entityIndex < playerData[playerIndex].tableEntities.size(); ++entityIndex)
    {
      std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(playerData[playerIndex].tableEntities[entityIndex]);
      if (minion)
      {
        if (minion->GetEntitiesType() == EntityType::BRAWL)
        {
          minion->applyEffect(playerData, playerIndex);
          removeEntityFromTable(playerIndex, entityIndex);
        }
        else if (minion->GetEntitiesType() == EntityType::SHAMAN && !minion->IsUsed())
        {
          minion->applyEffect(playerData, playerIndex);
          minion->SetIsUsed(true);
        }
        else if (minion->GetEntitiesType() != EntityType::SHAMAN)
        {

          minion->DameToAllEntities(playerData[1 - playerIndex], minion->GetAttack());
          minion->applyEffect(playerData, playerIndex);
          minion->SetIsUsed(true);
          totalMinionsDamage += minion->GetAttack();
        }
      }
      else
      {
        std::cout << " - Non-Minion entity" << std::endl;
      }
    }
  }
  tableEntitiesPlayer1.push_back(playerData[playerIndex].hero->GetName() + " attack " + playerData[1 - playerIndex].hero->GetName() + " with " + std::to_string(playerData[playerIndex].hero->GetAttack()) + " and minion attack with: [" + std::to_string(totalMinionsDamage) + "] damage");
  playerData[playerIndex].hero->AttackHero(playerData[1 - playerIndex].hero, playerData[playerIndex].hero->GetAttack());
  tableEntitiesPlayer1.push_back(playerData[playerIndex].hero->GetName() + "'s health left [" + std::to_string((playerData[playerIndex].hero->GetHealth())) + "]");
  console->clearConsole();
  console->displayTableStats(playerData[playerIndex].hero->GetName() + "'s table entities", tableEntitiesPlayer1);

  tableEntitiesPlayer2.push_back(playerData[1 - playerIndex].hero->GetName() + " have been attacked by " + playerData[playerIndex].hero->GetName() + " with " + std::to_string(playerData[playerIndex].hero->GetAttack()) + " and minion attack " + std::to_string(totalMinionsDamage));
  for (int i = 0; i < playerData[1 - playerIndex].stats.size(); i++)
  {
    tableEntitiesPlayer2.push_back(playerData[1 - playerIndex].stats[i]);
  }
  tableEntitiesPlayer2.push_back(playerData[1 - playerIndex].hero->GetName() + "'s health left [" + std::to_string((playerData[1 - playerIndex].hero->GetHealth())) + "]");
  console->displayTableStats(playerData[1 - playerIndex].hero->GetName() + "'s table stats", tableEntitiesPlayer2);
  tableEntitiesPlayer1.clear();
  tableEntitiesPlayer2.clear();
}
