#include "GameEngine/GameEngine.h"
#include "GameEntities/Entity.h"
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include "Helper/Helper.h"
GameEngine::GameEngine()
{
  srand(static_cast<unsigned int>(time(nullptr)));
  GameEngine_addUiObserver(&gameUi);
  GameEngine_notifyUiObserver(0,GameUi::INIT_STATE, option, GameData);
  GameEngine_generateHeroPocket();
  GameEngine_generateCardPocket();
  GameEngine_distributeCardToPlayerHand();
}

/**
 * @brief Initializes the game's heroes.
 */
void GameEngine::GameEngine_generateHeroPocket()
{
  playerHero.InitHeroes();
  std::vector<std::shared_ptr<Hero>> retrievedHeroes = playerHero.GetHeroes();
  GameData_t playerClient;
  GameData_t playerServer;
  int randomIndex = rand() % retrievedHeroes.size();
  playerClient.hero = retrievedHeroes[randomIndex];
  randomIndex = rand() % retrievedHeroes.size();
  playerServer.hero = retrievedHeroes[randomIndex];
  GameData.push_back(playerClient);
  GameData.push_back(playerServer);
}

/**
 * @brief Initializes the game's cards.
 */
void GameEngine::GameEngine_generateCardPocket()
{
  std::shared_ptr<Minion> minion = std::make_shared<FlametongueTotem>();

  cardsPool.push_back(std::make_shared<FlametongueTotem>());
  cardsPool.push_back(std::make_shared<RagnarosTheFirelord>());
  cardsPool.push_back(std::make_shared<BloodmageThalnos>());
  cardsPool.push_back(std::make_shared<Brawl>());
  cardsPool.push_back(std::make_shared<Techies>());
}

void GameEngine::GameEngine_generateEntitiesForEachMode(MySocket &socket)
{
  EntityType entities[(option == CLIENT_MODE ? GameData[0].handEntities.size() : 2 * GameData[0].handEntities.size())];
  int entitiesCount = 0;
  switch (option)
  {
  case CLIENT_MODE:
    if (socket.receiveInitCardPool(ClientData.handEntities, ServerData.handEntities))
    {
      GameData[CLIENT_INDEX].handEntities = ClientData.handEntities;
      GameData[SERVER_INDEX].handEntities = ServerData.handEntities;
    }

    return;
  case SERVER_MODE:
    for (int playerIndex = 0; playerIndex < 2; playerIndex++)
      for (auto &e : GameData[playerIndex].handEntities)
      {
        entities[entitiesCount] = e->GetEntitiesType();
        entitiesCount++;
      }
    socket.sendInitCardPool(entities);
    break;
  default:
    /* in ofline mode, data have been generated at begin, no need any actions*/
    break;
  }
}

void GameEngine::GameEngine_distributeCardToPlayerHand()
{
  for (auto &player : GameData)
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

void GameEngine::play()
{
  MySocket socket(option);
  while (true)
  {
    GameEngine_checkPlayerTurnCount(socket);
    GameEngine_notifyUiObserver(CLIENT_INDEX, GameUi::RESULT_STATE, option, GameData);
    switch (option)
    {
    case CLIENT_MODE:
      GameEngine_onClientMode(socket);
      break;
    case SERVER_MODE:
      GameEngine_onServerMode(socket);
      break;
    default:
      GameEngine_onOfflineMode();
      break;
    }
  }
}

void GameEngine::GameEngine_onClientMode(MySocket &socket)
{
  int cardChoiced;
  GameEngine_notifyUiObserver(CLIENT_INDEX, GameUi::CHOICE_STATE, cardChoiced, GameData);
  GameEngine_handingPlayerTurn(CLIENT_INDEX, cardChoiced);
  socket.sendPlayerChoice(cardChoiced);
  int serverChoiceCard = socket.receivePlayerChoice();
  GameEngine_handingPlayerTurn(SERVER_INDEX, serverChoiceCard);
}

void GameEngine::GameEngine_onServerMode(MySocket &socket)
{

  int clientChoiceCard = socket.receivePlayerChoice();
  GameEngine_handingPlayerTurn(CLIENT_INDEX, clientChoiceCard);
  int cardChoiced;
  GameEngine_notifyUiObserver(SERVER_INDEX, GameUi::CHOICE_STATE, cardChoiced, GameData);
  GameEngine_handingPlayerTurn(SERVER_INDEX, cardChoiced);
  socket.sendPlayerChoice(cardChoiced);
}

void GameEngine::GameEngine_checkPlayerTurnCount(MySocket &socket)
{
  for (int playerIndex = 0; playerIndex < GameData.size(); playerIndex++)
  {
    if (GameData[playerIndex].turnCount == 2)
    {
      for (int i = 0; i < 2; i++)
      {
        int randomIndex = rand() % cardsPool.size();
        std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(cardsPool[randomIndex]);
        if (minion)
        {
          GameData[playerIndex].handEntities.push_back(minion);
        }
      }
      GameData[playerIndex].turnCount = 0;
    }
  }
  if (option < 3)
    GameEngine_generateEntitiesForEachMode(socket);
}

void GameEngine::GameEngine_onOfflineMode()
{
  std::vector<std::string> cardList;
  while (true)
  {
    int cardChoiced;
    GameEngine_notifyUiObserver(CLIENT_INDEX, GameUi::CHOICE_STATE, cardChoiced, GameData);
    GameEngine_handingPlayerTurn(CLIENT_INDEX, cardChoiced);
    std::swap(CLIENT_INDEX, SERVER_INDEX);
  }
}

void GameEngine::clearPlayerDataStats()
{
  GameData[CLIENT_INDEX].stats.clear();
  GameData[SERVER_INDEX].stats.clear();
}

void GameEngine::GameEngine_handingPlayerTurn(int playerIndex, int choice)
{
  GameData[playerIndex].turnCount++;
  GameEngine_placeCardToBattleYard(playerIndex, choice);
  GameEngine_activeCardOnBattleYard(playerIndex);
  GameEngine_notifyUiObserver(playerIndex, GameUi::STATS_STATE, choice, GameData);
  clearPlayerDataStats();
}

void GameEngine::GameEngine_deleteCardFromBattleYard(int playerIndex, int entityIndex)
{
  if (entityIndex < GameData[playerIndex].tableEntities.size())
  {
    GameData[playerIndex].stats.push_back(GameData[playerIndex].hero->GetName() + " remove " + GameData[playerIndex].tableEntities[entityIndex]->GetDescription());
    GameData[playerIndex].tableEntities.erase(GameData[playerIndex].tableEntities.begin() + entityIndex);
  }
}

void GameEngine::GameEngine_placeCardToBattleYard(int playerIndex, int entityIndex)
{

  if (entityIndex < GameData[playerIndex].handEntities.size())
  {
    std::shared_ptr<GameEntity> originalEntity = GameData[playerIndex].handEntities[entityIndex];

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
    else if (originalEntity->GetEntitiesType() == EntityType::FIRELORD)
    {
      auto minionEntity = std::dynamic_pointer_cast<RagnarosTheFirelord>(originalEntity);
      if (minionEntity)
      {
        newEntity = std::make_shared<RagnarosTheFirelord>(*minionEntity);
      }
    }
    else if (originalEntity->GetEntitiesType() == EntityType::THALNOS)
    {
      auto bloodmageEntity = std::dynamic_pointer_cast<BloodmageThalnos>(originalEntity);
      if (bloodmageEntity)
      {
        newEntity = std::make_shared<BloodmageThalnos>(*bloodmageEntity);
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
      GameData[playerIndex].tableEntities.push_back(newEntity);
      GameData[playerIndex].stats.push_back(GameData[playerIndex].hero->GetName() + " activate " + newEntity->GetDescription());
      GameData[playerIndex].handEntities.erase(GameData[playerIndex].handEntities.begin() + entityIndex);
    }
  }
}

void GameEngine::GameEngine_activeCardOnBattleYard(int playerIndex)
{
  int totalMinionsDamage = 0;
  if (!GameData[playerIndex].tableEntities.empty())
  {
    for (size_t entityIndex = 0; entityIndex < GameData[playerIndex].tableEntities.size(); ++entityIndex)
    {
      std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(GameData[playerIndex].tableEntities[entityIndex]);
    }

    for (size_t entityIndex = 0; entityIndex < GameData[playerIndex].tableEntities.size(); ++entityIndex)
    {
      std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>(GameData[playerIndex].tableEntities[entityIndex]);
      if (minion)
      {
        if (minion->GetEntitiesType() == EntityType::BRAWL)
        {
          minion->applyEffect(GameData, playerIndex);
          GameEngine_deleteCardFromBattleYard(playerIndex, entityIndex);
        }
        else if (minion->GetEntitiesType() == EntityType::SHAMAN && !minion->IsUsed())
        {
          minion->applyEffect(GameData, playerIndex);
          minion->SetIsUsed(true);
        }
        else if (minion->GetEntitiesType() != EntityType::SHAMAN)
        {

          minion->DameToAllEntities(GameData[1 - playerIndex], minion->GetAttack());
          minion->applyEffect(GameData, playerIndex);
          minion->SetIsUsed(true);
          totalMinionsDamage += minion->GetAttack();
        }
      }
    }
  }
  GameData[playerIndex].stats.push_back(GameData[playerIndex].hero->GetName() + " attack " + GameData[1 - playerIndex].hero->GetName() + " with " + std::to_string(GameData[playerIndex].hero->GetAttack()) + " and minion attack with: [" + std::to_string(totalMinionsDamage) + "] damage");
  GameData[playerIndex].hero->AttackHero(GameData[1 - playerIndex].hero, GameData[playerIndex].hero->GetAttack());
  GameData[playerIndex].stats.push_back(GameData[playerIndex].hero->GetName() + "'s health left [" + std::to_string((GameData[playerIndex].hero->GetHealth())) + "]");

  GameData[1 - playerIndex].stats.push_back(GameData[1 - playerIndex].hero->GetName() + " have been attacked by " + GameData[playerIndex].hero->GetName() + " with " + std::to_string(GameData[playerIndex].hero->GetAttack()) + " and minion attack " + std::to_string(totalMinionsDamage));

  GameData[1 - playerIndex].stats.push_back(GameData[1 - playerIndex].hero->GetName() + "'s health left [" + std::to_string((GameData[1 - playerIndex].hero->GetHealth())) + "]");
}

void GameEngine::GameEngine_addUiObserver(GameUi *uiObs)
{
  observers.push_back(uiObs);
}

void GameEngine::GameEngine_notifyUiObserver(int playerIndex,int state, int &cardChoiced, const std::vector<GameData_t> &tableData)
{
  for (GameUi* observer : observers) {
            observer->GameUi_updateGameState(playerIndex, state, cardChoiced, tableData );
  }
}