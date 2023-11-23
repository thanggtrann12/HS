#include "Engine/Engine.h"
#include <iostream>
#include <string>
#include "Hero/Hero.h"
#include <ctime>
Engine::Engine(Player &player1, Player &player2, Ui *ui) : playerLists{player1, player2}
{
    addUiObserver(ui);
}

void Engine::startGame()
{
    std::srand(std::time(0));
    playerLists[hostPlayerID].setHero(BUTCHER);
    playerLists[clientPlayerID].setHero(SLARK);
    if (currentGameMode == UNKNOWN)
    {
        updateUi(Ui::INIT, playerLists, MAX_PLAYER, (unsigned int &)currentGameMode);
        for (int playerIndex = 0; playerIndex < (unsigned int)MAX_PLAYER; playerIndex++)
        {
            playerLists[playerIndex].drawCard(10);
        }
    }

    MySocket socket((unsigned int)currentGameMode);
    switch (currentGameMode)
    {
    case HOST:
    {
        auto &serverSocket = socket;
        startHostMode(&serverSocket);
        break;
    }
    case CLIENT:
    {
        auto &clientSocket = socket;
        for (int playerIndex = 0; playerIndex < (unsigned int)MAX_PLAYER; playerIndex++)
        {
            playerLists[playerIndex].getHand().clear();
        }
        startClientMode(&clientSocket);
        break;
    }
    default:
        startSingleMode();
        break;
    }
}

bool Engine::isEndGame(PlayerId playerID)
{
    return playerLists[playerID].getHero()->IsAlive();
}

void Engine::endTurn()
{
    std::swap(currentTurn, nextTurn);
}

void Engine::startHostMode(MySocket *host)
{
    while (true)
    {

        if (host != nullptr)
        {
            auto &hostPlayer = playerLists[hostPlayerID];
            auto &clientPlayer = playerLists[clientPlayerID];

            generateCardsForEachMode(host, hostPlayer, nullptr, clientPlayer);
            // Host receives client's choice
            unsigned int clientChoiceCard = host->receivePlayerChoice();
            // Handle client's turn
            handlingPlayerTurn(clientPlayerID, clientChoiceCard, playerLists);
            updateUi(Ui::WAIT_FOR_CONFIRM, playerLists, hostPlayerID, clientChoiceCard);

            // Host plays its card
            unsigned int cardPlayed = hostPlayer.pickACardToPlay();
            host->sendPlayerChoice(cardPlayed);

            // Handle host's turn
            handlingPlayerTurn(hostPlayerID, cardPlayed, playerLists);
            updateUi(Ui::WAIT_NEXT_TURN, playerLists, hostPlayerID, clientChoiceCard);
            roundCount++;
        }
    }
}

void Engine::startClientMode(MySocket *client)
{
    while (true)
    {

        if (client != nullptr)
        {
            auto &hostPlayer = playerLists[hostPlayerID];
            auto &clientPlayer = playerLists[clientPlayerID];

            // Client receives host's card choices
            generateCardsForEachMode(nullptr, hostPlayer, client, clientPlayer);
            // Client plays its card
            unsigned int cardPlayed = clientPlayer.pickACardToPlay();
            client->sendPlayerChoice(cardPlayed);
            // Handle client's turn
            handlingPlayerTurn(clientPlayerID, cardPlayed, playerLists);
            updateUi(Ui::WAIT_NEXT_TURN, playerLists, clientPlayerID, cardPlayed);

            // Client receives host's choice
            unsigned int serverChoiceCard = client->receivePlayerChoice();

            // Handle host's turn
            handlingPlayerTurn(hostPlayerID, serverChoiceCard, playerLists);
            updateUi(Ui::WAIT_FOR_CONFIRM, playerLists, hostPlayerID, serverChoiceCard);
        }
    }
}

void Engine::startSingleMode()
{
    unsigned int cardChoiced;
    while (true)
    {
        auto &currentPlayer = playerLists[currentTurn];
        auto &opponentPlayer = playerLists[nextTurn];
        unsigned int cardPlayed = currentPlayer.pickACardToPlay();
        handlingPlayerTurn((PlayerId)currentTurn, cardPlayed, playerLists);
        generateCardsForEachMode(nullptr, currentPlayer, nullptr, opponentPlayer);
        updateUi(Ui::WAIT_FOR_CONFIRM, playerLists, (PlayerId)currentTurn, cardPlayed);
        endTurn();
        roundCount++;
    }
    updateUi(Ui::RESULT, playerLists, (PlayerId)currentTurn, cardChoiced);
}

void Engine::handlingPlayerTurn(PlayerId playerID, unsigned int cardPlayed, std::vector<Player> &players)
{
    auto cardIterator = players[playerID].getHand().begin() + cardPlayed;
    for (size_t playerIndex = 0; playerIndex < MAX_PLAYER; playerIndex++)
    {
        if (!players[playerIndex].getHero()->IsAlive())
            updateUi(Ui::RESULT, players, (PlayerId)(1 - playerIndex), cardPlayed);
    }

    players[playerID].activeCardOnHand(players[playerID], players[1 - playerID], cardIterator);

    generateCardsForEachMode(nullptr, players[playerID], nullptr, players[1 - playerID]);
    updateUi(Ui::UPDATE_BATTLE, players, playerID, cardPlayed);
    for (size_t playerIndex = 0; playerIndex < MAX_PLAYER; playerIndex++)
    {
        players[playerIndex].stats.clear();
    }
}

void Engine::generateCardsForEachMode(MySocket *host, Player &hostPlayer, MySocket *client, Player &clientPlayer)
{

    switch (currentGameMode)
    {
    case CLIENT:
        if (client != nullptr)
        {
            client->recvInitCardPool(hostPlayer, clientPlayer);
        }
        break;
    case HOST:
        if (roundCount == 3)
        {
            hostPlayer.drawCard(1);
            clientPlayer.drawCard(1);
            roundCount = 0;
        }

        if (host != nullptr)
        {
            host->sendInitCardPool(hostPlayer.getHand(), clientPlayer.getHand());
        }
        break;
    default:
        if (roundCount == 3)
        {
            hostPlayer.drawCard(1);
            clientPlayer.drawCard(1);
            hostPlayer.stats.push_back(hostPlayer.getBasicInfo() + " draw " + hostPlayer.getHand().at(hostPlayer.getHand().size() - 1)->getDesciption());
            clientPlayer.stats.push_back(clientPlayer.getBasicInfo() + " draw " + clientPlayer.getHand().at(clientPlayer.getHand().size() - 1)->getDesciption());
            roundCount = 0;
        }
        break;
    }
}

void Engine::addUiObserver(Ui *subUi)
{
    uiObs = subUi;
}

void Engine::updateUi(Ui::UiState state, std::vector<Player> &players, PlayerId playerId, unsigned int &clone)
{
    uiObs->updateUiOnState(state, players, playerId, clone);
}

Engine::~Engine()
{
}