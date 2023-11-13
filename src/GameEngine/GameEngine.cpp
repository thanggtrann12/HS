#include "GameEngine/GameEngine.h"
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include "Helper/Helper.h"
#include <limits>
GameEngine::GameEngine()
{
    GameData.resize(2);
    srand(static_cast<unsigned int>(time(nullptr)));
    GameEngine_addUiObserver(&gameUi);
    GameEngine_notifyUiObserver(MASTER, GameUi::INIT, option, GameData);
    GameEngine_generatePlayerHero();
    GameEngine_generatePlayerCards();
}

void GameEngine::GameEngine_generatePlayerHero()
{
    for (int playerIndex = 0; playerIndex < MASTER; playerIndex++)
        GameData[playerIndex].hero = manager.CardManager_assignHeroToPlayer(playerIndex);
}

void GameEngine::GameEngine_generatePlayerCards()
{
    for (auto &player : GameData)
    {
        manager.CardManager_getCardFromPocket(player.handCard);
    }
}

void GameEngine::GameEngine_generateEntitiesForEachMode(MySocket &socket)
{
    switch (option)
    {
    case CLIENT_MODE:
    {
        GameData[PLAYER_1].handCard.clear();
        GameData[PLAYER_2].handCard.clear();

        Card::CardType *client = nullptr;
        Card::CardType *host = nullptr;
        int clientSize = 0, hostSize = 0;

        socket.recvInitCardPool(host, hostSize, client, clientSize);

        if (host && client)
        {
            for (int i = 0; i < hostSize; i++)
            {
                manager.CardManager_pushCardToTable(GameData[PLAYER_2].handCard, host[i]);
            }

            for (int i = 0; i < clientSize; i++)
            {
                manager.CardManager_pushCardToTable(GameData[PLAYER_1].handCard, client[i]);
            }

            delete[] host;
            delete[] client;
        }
    }
    break;

    case SERVER_MODE:
    {
        int clientCount = 0;
        Card::CardType *client = new Card::CardType[GameData[PLAYER_1].handCard.size()];
        for (auto &e : GameData[PLAYER_1].handCard)
        {
            client[clientCount] = e->getCardType();
            clientCount++;
        }

        int hostCount = 0;
        Card::CardType *host = new Card::CardType[GameData[PLAYER_2].handCard.size()];
        for (auto &e : GameData[PLAYER_2].handCard)
        {
            host[hostCount] = e->getCardType();
            hostCount++;
        }

        socket.sendInitCardPool(host, hostCount, client, clientCount);

        delete[] host;
        delete[] client;
    }
    break;
    }
}

void GameEngine::play()
{
    MySocket socket(option);
    GameEngine_generateEntitiesForEachMode(socket);
    while (true)
    {
        GameEngine_checkPlayerTurnCount(socket);
        GameEngine_notifyUiObserver(PLAYER_1, GameUi::RESULT, option, GameData);
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
    GameEngine_notifyUiObserver(PLAYER_1, GameUi::CHOICE, cardChoiced, GameData);
    socket.sendPlayerChoice(cardChoiced);
    GameEngine_handingPlayerTurn(PLAYER_1, cardChoiced);
    GameEngine_notifyUiObserver(PLAYER_1, GameUi::WAIT_NEXT_TURN, cardChoiced, GameData);
    int serverChoiceCard = socket.receivePlayerChoice();
    GameEngine_handingPlayerTurn(PLAYER_2, serverChoiceCard);
    GameEngine_notifyUiObserver(PLAYER_2, GameUi::WAIT_CONFIRM, serverChoiceCard, GameData);
}

void GameEngine::GameEngine_onServerMode(MySocket &socket)
{

    int clientChoiceCard = socket.receivePlayerChoice();
    GameEngine_handingPlayerTurn(PLAYER_1, clientChoiceCard);
    GameEngine_notifyUiObserver(PLAYER_1, GameUi::WAIT_CONFIRM, clientChoiceCard, GameData);
    int cardChoiced;
    GameEngine_notifyUiObserver(PLAYER_2, GameUi::CHOICE, cardChoiced, GameData);
    socket.sendPlayerChoice(cardChoiced);
    GameEngine_handingPlayerTurn(PLAYER_2, cardChoiced);
    GameEngine_notifyUiObserver(PLAYER_2, GameUi::WAIT_NEXT_TURN, clientChoiceCard, GameData);
}

void GameEngine::GameEngine_checkPlayerTurnCount(MySocket &socket)
{
    for (int player = 0; player < GameData.size(); player++)
    {
        if (GameData[player].turnCount == 2)
        {
            std::shared_ptr<Card> minion = std::dynamic_pointer_cast<Card>(manager.CardManager_drawRandomCard());
            if (minion)
            {
                GameData[player].handCard.push_back(minion);
                GameData[player].stats.push_back("Player " + std::to_string(player) + " draw [" + minion->getDesciption() + "]");
            }
            GameData[player].turnCount = 0;
            // GameEngine_generateEntitiesForEachMode(socket);
        }
    }
}

void GameEngine::GameEngine_onOfflineMode()
{
    int currentPlayer = PLAYER_1;
    int opponentPlayer = PLAYER_2;
    while (true)
    {
        int cardChoiced;
        MySocket socket(option);
        GameEngine_checkPlayerTurnCount(socket);
        GameEngine_notifyUiObserver((player_t)currentPlayer, GameUi::RESULT, cardChoiced, GameData);
        GameEngine_notifyUiObserver((player_t)currentPlayer, GameUi::CHOICE, cardChoiced, GameData);
        GameEngine_handingPlayerTurn((player_t)currentPlayer, cardChoiced);
        GameEngine_notifyUiObserver((player_t)currentPlayer, GameUi::WAIT_CONFIRM, cardChoiced, GameData);
        std::swap(currentPlayer, opponentPlayer);
    }
}

void GameEngine::clearPlayerDataStats()
{
    GameData[PLAYER_1].stats.clear();
    GameData[PLAYER_2].stats.clear();
}

void GameEngine::GameEngine_handingPlayerTurn(player_t player, int choice)
{
    GameData[player].turnCount++;
    GameData[player].hero->attackDefenderHero(GameData[1 - player]);
    GameEngine_activeCard(player, choice);
    GameEngine_notifyUiObserver(player, GameUi::STATS, choice, GameData);
    clearPlayerDataStats();
}

void GameEngine::GameEngine_activeCard(player_t player, int entityIndex)
{

    if (entityIndex < GameData[player].handCard.size())
    {
        std::shared_ptr<Card> originalEntity = GameData[player].handCard[entityIndex];

        if (!originalEntity)
        {
            return;
        }
        else
        {
            GameData[player].stats.push_back(GameData[player].hero->getName() + " activate " + originalEntity->getName());
            originalEntity->setUsed();
            manager.CardManager_pushCardToTable(GameData[player].tableEntities, originalEntity->getCardType());
            originalEntity->play(player, GameData[player].tableEntities.end() - 1, GameData);
            GameData[player].handCard.erase(GameData[player].handCard.begin() + entityIndex);
        }
    }
}

void GameEngine::GameEngine_addUiObserver(GameUi *uiObs)
{
    observers.push_back(uiObs);
}

void GameEngine::GameEngine_notifyUiObserver(player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData)
{
    for (GameUi *observer : observers)
    {
        observer->GameUi_updateGameState(player, state, cardChoiced, tableData);
    }
}