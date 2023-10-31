#include "Game/Game.h"
#include "Entity/Entity.h"
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include "Helper/Helper.h"
Game::Game()
{
  srand(static_cast<unsigned int>(time(nullptr)));
  LOG_I("Display welcome console with mode: ");
  console->displayWelcomeMessage(mode);
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
    LOG_D("Player [%s] receive: ", player.hero->GetName().c_str());
    for (int i = 0; i < 10; ++i)
    {
      int randomIndex = rand() % cardsPool.size();
      std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(cardsPool[randomIndex]);
      if (minion)
      {
        player.handEntities.push_back(minion);
        LOG_D(" [%d] %s ", i + 1, minion->GetDescription().c_str());
      }
    }
  }
}
void ClearGameStats(GameStats_t &stats)
{
  stats.basicHeroStats.clear();
  stats.stats.clear();
  stats.cardNames.clear();
  stats.cardTypes.clear();
  stats.cardSkills.clear();
  stats.health.clear();
  stats.attack.clear();
  stats.activate.clear();
}

void Game::play()
{
  MySocket socket(mode);

  console->loadingConsole();
  console->clearConsole();
  while (true)
  {
    switch (mode)
    {
    case CLIENT_MODE:
      playClientMode(socket);
      break;
    case SERVER_MODE:
      playServerMode(socket);
      break;
    default:
      playOfflineMode();
      break;
    }
  }
}

void Game::playClientMode(MySocket &socket)
{
  std::vector<std::string> handEntities;
  GameStats_t playerClient;
  GameStats_t playerServer;
  if (socket.receiveHandEntities(handEntities) == 0)
  {
    int cardChoice = console->displayMenu(playerData[CLIENT_INDEX].hero->GetName() + "'s HP [" + std::to_string(playerData[CLIENT_INDEX].hero->GetHealth()) + "] turn with round [" + std::to_string(playerData[CLIENT_INDEX].turnCount + 1) + "]", handEntities);
    socket.sendPlayerChoice(cardChoice);

    socket.receiveGameStats(playerClient, playerServer);
    showEntitiesOnTable(playerClient, playerServer);
    ClearGameStats(playerServer);
    ClearGameStats(playerClient);
    std::cout << "Wait for other turn" << std::endl;
    socket.receiveGameStats(playerServer, playerClient);
    showEntitiesOnTable(playerServer, playerClient);
    ClearGameStats(playerServer);
    ClearGameStats(playerClient);
    console->waitForEnter();
  }
  clearPlayerDataStats();
}

void Game::playServerMode(MySocket &socket)
{
  std::vector<std::string> cardList;
  for (auto &currentPlayerCard : playerData[CLIENT_INDEX].handEntities)
  {
    cardList.push_back(currentPlayerCard->GetDescription());
  }
  socket.sendPlayerHandEntities(playerData[CLIENT_INDEX]);
  int playerChoice = socket.receivePlayerChoice();
  addEntityToTable(CLIENT_INDEX, playerChoice);
  removeEntityFromHand(CLIENT_INDEX, playerChoice);
  activateEntity(CLIENT_INDEX);
  showTableStats(CLIENT_INDEX);
  GameStats_t currentPlayer = getGameStatsForPlayer(CLIENT_INDEX);
  GameStats_t opponentPlayer = getGameStatsForPlayer(SERVER_INDEX);
  socket.sendGameStats(currentPlayer, opponentPlayer);
  ClearGameStats(currentPlayer);
  ClearGameStats(opponentPlayer);
  console->waitForEnter();
  playerData[CLIENT_INDEX].stats.clear();
  playerData[SERVER_INDEX].stats.clear();
  cardList.clear();
  for (auto &currentPlayerCard : playerData[SERVER_INDEX].handEntities)
  {
    cardList.push_back(currentPlayerCard->GetDescription());
  }
  int cardChoice = console->displayMenu(playerData[SERVER_INDEX].hero->GetName() + "'s HP [" + std::to_string(playerData[SERVER_INDEX].hero->GetHealth()) + "] turn with round [" + std::to_string(playerData[CLIENT_INDEX].turnCount + 1) + "]", cardList);
  addEntityToTable(SERVER_INDEX, playerChoice);
  removeEntityFromHand(SERVER_INDEX, playerChoice);
  activateEntity(SERVER_INDEX);
  showTableStats(SERVER_INDEX);

  currentPlayer = getGameStatsForPlayer(SERVER_INDEX);
  opponentPlayer = getGameStatsForPlayer(CLIENT_INDEX);
  socket.sendGameStats(currentPlayer, opponentPlayer);
  playerData[CLIENT_INDEX].stats.clear();
  playerData[SERVER_INDEX].stats.clear();
  cardList.clear();
  std::cout << "Wait for other turn" << std::endl;
  clearPlayerDataStats();
}

void Game::playOfflineMode()
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
        showTableStats(CLIENT_INDEX);
        cardList.clear();
        clearPlayerDataStats();
      }
      else
      {
        console->clearConsole();
        std::cout << "Player Winner: " + playerData[SERVER_INDEX].hero->GetDescription() << std::endl;
        console->waitForEnter();
      }
    }
    console->waitForEnter();

    std::swap(CLIENT_INDEX, SERVER_INDEX);
  }
}

void Game::clearPlayerDataStats()
{
  playerData[CLIENT_INDEX].stats.clear();
  playerData[SERVER_INDEX].stats.clear();
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
  }
}

void Game::addEntityToTable(int playerIndex, int entityIndex)
{
  if (entityIndex < playerData[playerIndex].handEntities.size())
  {
    std::shared_ptr<GameEntity> originalEntity = playerData[playerIndex].handEntities[entityIndex];

    if (!originalEntity)
    {
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
    }
  }
  playerData[playerIndex].stats.push_back(playerData[playerIndex].hero->GetName() + " attack " + playerData[1 - playerIndex].hero->GetName() + " with " + std::to_string(playerData[playerIndex].hero->GetAttack()) + " and minion attack with: [" + std::to_string(totalMinionsDamage) + "] damage");
  playerData[playerIndex].hero->AttackHero(playerData[1 - playerIndex].hero, playerData[playerIndex].hero->GetAttack());
  playerData[playerIndex].stats.push_back(playerData[playerIndex].hero->GetName() + "'s health left [" + std::to_string((playerData[playerIndex].hero->GetHealth())) + "]");

  playerData[1 - playerIndex].stats.push_back(playerData[1 - playerIndex].hero->GetName() + " have been attacked by " + playerData[playerIndex].hero->GetName() + " with " + std::to_string(playerData[playerIndex].hero->GetAttack()) + " and minion attack " + std::to_string(totalMinionsDamage));

  playerData[1 - playerIndex].stats.push_back(playerData[1 - playerIndex].hero->GetName() + "'s health left [" + std::to_string((playerData[1 - playerIndex].hero->GetHealth())) + "]");
}

GameStats_t Game::getGameStatsForPlayer(int playerIndex)
{
  GameStats_t player;

  for (auto &entity : playerData[playerIndex].tableEntities)
  {
    player.cardNames.push_back(entity->GetName());
    player.cardTypes.push_back(entity->EntityTypeToString(entity->GetEntitiesType()));
    player.cardSkills.push_back(entity->GetSkill());
    player.health.push_back(std::to_string(entity->GetHealth()));
    player.attack.push_back(std::to_string(entity->GetAttack()));
    player.activate.push_back(entity->IsUsed() ? "ACTIVE" : "INACTIVE");
  }

  player.stats = playerData[playerIndex].stats;
  player.basicHeroStats = formatBasicHeroStats(playerData[playerIndex].hero->GetName(),
                                               playerData[playerIndex].hero->GetHealth(),
                                               playerData[playerIndex].turnCount);

  return player;
}

std::string Game::formatBasicHeroStats(const std::string &heroName, int health, int turnCount)
{
  return heroName + "'s HP [" + std::to_string(health) + "] turn [" + std::to_string(turnCount) + "]";
}

void Game::showTableStats(int playerIndex)
{
  GameStats_t currentPlayer = getGameStatsForPlayer(playerIndex);
  GameStats_t opponentPlayer = getGameStatsForPlayer(1 - playerIndex);

  showEntitiesOnTable(currentPlayer, opponentPlayer);
}

void Game::showEntitiesOnTable(const GameStats_t &currentPlayer, const GameStats_t &opponentPlayer)
{
  console->clearConsole();

  console->displayTableStats(currentPlayer.basicHeroStats, currentPlayer.stats);
  console->displayHandEntities(currentPlayer);
  std::cout << "\n\n\n";
  console->displayHandEntities(opponentPlayer);
  console->displayTableStats(opponentPlayer.basicHeroStats, opponentPlayer.stats);
}