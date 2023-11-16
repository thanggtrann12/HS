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
    addUiObserver(&gameUi);
    notifyUiObserver(MAX_PLAYER, GameUi::INIT, option, GameData);
    generatePlayerHero();
    generatePlayerCards();
}

void GameEngine::generatePlayerHero()
{
    for (int playerIndex = 0; playerIndex < MAX_PLAYER; playerIndex++)
        GameData[playerIndex].hero = manager.assignHeroToPlayer(playerIndex);
}

void GameEngine::generatePlayerCards()
{
    for (auto &player : GameData)
    {
        manager.getCardFromPocket(player.handCard);
    }
}

void GameEngine::generateEntitiesForEachMode(MySocket &socket)
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
                manager.pushCardToTable(GameData[PLAYER_2].handCard, host[i]);
            }

            for (int i = 0; i < clientSize; i++)
            {
                manager.pushCardToTable(GameData[PLAYER_1].handCard, client[i]);
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
    generateEntitiesForEachMode(socket);
    while (true)
    {
        checkPlayerTurnCount(socket);
        notifyUiObserver(PLAYER_1, GameUi::RESULT, option, GameData);
        switch (option)
        {
        case CLIENT_MODE:
            onClientMode(socket);
            break;
        case SERVER_MODE:
            onServerMode(socket);
            break;
        default:
            onOfflineMode();
            break;
        }
    }
}

void GameEngine::onClientMode(MySocket &socket)
{
    int cardChoiced;
    notifyUiObserver(PLAYER_1, GameUi::CHOICE, cardChoiced, GameData);
    socket.sendPlayerChoice(cardChoiced);
    handingPlayerTurn(PLAYER_1, cardChoiced);
    notifyUiObserver(PLAYER_1, GameUi::WAIT_NEXT_TURN, cardChoiced, GameData);
    int serverChoiceCard = socket.receivePlayerChoice();
    handingPlayerTurn(PLAYER_2, serverChoiceCard);
    notifyUiObserver(PLAYER_2, GameUi::WAIT_CONFIRM, serverChoiceCard, GameData);
}

void GameEngine::onServerMode(MySocket &socket)
{

    int clientChoiceCard = socket.receivePlayerChoice();
    handingPlayerTurn(PLAYER_1, clientChoiceCard);
    notifyUiObserver(PLAYER_1, GameUi::WAIT_CONFIRM, clientChoiceCard, GameData);
    int cardChoiced;
    notifyUiObserver(PLAYER_2, GameUi::CHOICE, cardChoiced, GameData);
    socket.sendPlayerChoice(cardChoiced);
    handingPlayerTurn(PLAYER_2, cardChoiced);
    notifyUiObserver(PLAYER_2, GameUi::WAIT_NEXT_TURN, clientChoiceCard, GameData);
}

void GameEngine::checkPlayerTurnCount(MySocket &socket)
{
    for (int player = 0; player < GameData.size(); player++)
    {
        if (GameData[player].turnCount == 2)
        {
            std::shared_ptr<Card> minion = std::dynamic_pointer_cast<Card>(manager.drawRandomCard());
            if (minion)
            {
                GameData[player].handCard.push_back(minion);
                GameData[player].stats.push_back("Player " + std::to_string(player) + " draw [" + minion->getDesciption() + "]");
            }
            GameData[player].turnCount = 0;
            // generateEntitiesForEachMode(socket);
        }
    }
}

void GameEngine::onOfflineMode()
{
    int currentPlayer = PLAYER_1;
    int opponentPlayer = PLAYER_2;
    while (true)
    {
        int cardChoiced;
        MySocket socket(option);
        checkPlayerTurnCount(socket);
        notifyUiObserver((player_t)currentPlayer, GameUi::RESULT, cardChoiced, GameData);
        notifyUiObserver((player_t)currentPlayer, GameUi::CHOICE, cardChoiced, GameData);
        handingPlayerTurn((player_t)currentPlayer, cardChoiced);
        notifyUiObserver((player_t)currentPlayer, GameUi::WAIT_CONFIRM, cardChoiced, GameData);
        std::swap(currentPlayer, opponentPlayer);
    }
}

void GameEngine::clearPlayerDataStats()
{
    GameData[PLAYER_1].stats.clear();
    GameData[PLAYER_2].stats.clear();
}

void GameEngine::handingPlayerTurn(player_t player, int choice)
{
    GameData[player].turnCount++;
    GameData[player].hero->attackDefenderHero(GameData[1 - player]);
    activeCard(player, choice);
    notifyUiObserver(player, GameUi::STATS, choice, GameData);
    clearPlayerDataStats();
}

void GameEngine::activeCard(player_t player, int entityIndex)
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
            manager.pushCardToTable(GameData[player].tableEntities, originalEntity->getCardType());
            originalEntity->play(player, GameData[player].tableEntities.end() - 1, GameData);
            GameData[player].handCard.erase(GameData[player].handCard.begin() + entityIndex);
        }
    }
}

void GameEngine::addUiObserver(GameUi *uiObs)
{
    observers.push_back(uiObs);
}

void GameEngine::notifyUiObserver(player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData)
{
    for (GameUi *observer : observers)
    {
        observer->updateGameState(player, state, cardChoiced, tableData);
    }
}