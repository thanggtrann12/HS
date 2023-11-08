#include "GameEngine/GameEngine.h"
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
    GameData.resize(2);
    srand(static_cast<unsigned int>(time(nullptr)));
    GameEngine_addUiObserver(&gameUi);
    GameEngine_notifyUiObserver(0, GameUi::INIT_STATE, option, GameData);
    GameEngine_generatePlayerHero();
    GameEngine_generatePlayerCards();
}

void GameEngine::GameEngine_generatePlayerHero()
{
    for (auto &player : GameData)
    {
        manager.CardManager_assignHeroToPlayer(player.hero);
    }
}

void GameEngine::GameEngine_generatePlayerCards()
{
    for (auto &player : GameData)
    {
        manager.CardManager_getCardFromPocket(player.handEntities);
    }
}

void GameEngine::GameEngine_generateEntitiesForEachMode(MySocket &socket)
{
    Card::CardType entities[(option == CLIENT_MODE ? GameData[0].handEntities.size() : 2 * GameData[0].handEntities.size())];
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
                entities[entitiesCount] = e->getCardType();
                entitiesCount++;
            }
        socket.sendInitCardPool(entities);
        break;
    default:
        /* in ofline mode, data have been generated at begin, no need any actions*/
        break;
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
            std::shared_ptr<Card> minion = std::dynamic_pointer_cast<Card>(manager.CardManager_drawRandomCard());
            if (minion)
            {
                GameData[playerIndex].handEntities.push_back(minion);
            }
            GameData[playerIndex].turnCount = 0;
        }
    }
    if (option < 3)
        GameEngine_generateEntitiesForEachMode(socket);
}

void GameEngine::GameEngine_onOfflineMode()
{
    while (true)
    {
        int cardChoiced;
        MySocket socket(option);
        GameEngine_checkPlayerTurnCount(socket);
        GameEngine_notifyUiObserver(CLIENT_INDEX, GameUi::RESULT_STATE, cardChoiced, GameData);
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
    GameData[playerIndex].hero->attackDefenderHero(GameData[1 - playerIndex]);
    GameEngine_activeCard(playerIndex, choice);
    GameEngine_notifyUiObserver(playerIndex, GameUi::STATS_STATE, choice, GameData);
    clearPlayerDataStats();
}

void GameEngine::GameEngine_activeCard(int playerIndex, int entityIndex)
{

    if (entityIndex < GameData[playerIndex].handEntities.size())
    {
        std::shared_ptr<Card> originalEntity = GameData[playerIndex].handEntities[entityIndex];

        if (!originalEntity)
        {
            return;
        }
        else
        {
            manager.CardManager_pushCardToTable(GameData[playerIndex].tableEntities, originalEntity->getCardType());
            GameData[playerIndex].stats.push_back(GameData[playerIndex].hero->getName() + " activate " + originalEntity->getName());
            originalEntity->play(playerIndex, entityIndex, GameData);
            GameData[playerIndex].handEntities.erase(GameData[playerIndex].handEntities.begin() + entityIndex);
        }
    }
}

void GameEngine::GameEngine_addUiObserver(GameUi *uiObs)
{
    observers.push_back(uiObs);
}

void GameEngine::GameEngine_notifyUiObserver(int playerIndex, int state, int &cardChoiced, const std::vector<GameData_t> &tableData)
{
    for (GameUi *observer : observers)
    {
        observer->GameUi_updateGameState(playerIndex, state, cardChoiced, tableData);
    }
}