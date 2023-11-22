#include "Engine/Engine.h"
#include <iostream>
#include <string>
#include "Hero/Hero.h"
#include <ctime>

constexpr unsigned int INITIAL_CARD_COUNT = 10;

Engine::Engine(Player& player1, Player& player2, Ui* ui) : playerLists{player1, player2}
{
    registerUiModule(ui);
}

void Engine::initializeOperationMode()
{
  onUiStateChange(Ui::INITIALIZING, playerLists, MAX_PLAYER, (unsigned int&)(currentGameMode));

  switch (currentGameMode)
  {
  case MySocket::Mode::HOST:
    for (auto &player: playerLists)
    {
      player.drawCard(INITIAL_CARD_COUNT);
    }
    if (mySocket->registerSocketMode(MySocket::Mode::HOST) == true)
    {
      if(mySocket->waitForClientConnect()== true)
      {
        updatePlayerHandCard(playerLists[hostPlayerID], playerLists[clientPlayerID]);
      }
    }
    break;
  case MySocket::Mode::CLIENT:
    if(mySocket->registerSocketMode(MySocket::Mode::CLIENT)== true)
    {
      updatePlayerHandCard(playerLists[hostPlayerID], playerLists[clientPlayerID]);
    }
    break;
  default:
    for (auto &player: playerLists)
    {
      player.drawCard(INITIAL_CARD_COUNT);
    }
    break;
  }

}

void Engine::startGame()
{
    initializeOperationMode();
    std::srand(std::time(0));

    playerLists[hostPlayerID].setHero(BUTCHER);
    playerLists[clientPlayerID].setHero(SLARK);

    switch (currentGameMode)
    {
        case MySocket::Mode::HOST:
            processHostPlayerTurn();
            break;

        case MySocket::Mode::CLIENT:
            processClientPlayerTurn();
            break;

        default:
            processSinglePlayerTurn();
            break;
    }
}

bool Engine::isGameOver(PlayerId playerID)
{
    return !playerLists[playerID].getHero()->IsAlive();
}

void Engine::endTurnForPlayer()
{
    std::swap(currentTurn, nextTurn);
}

void Engine::processHostPlayerTurn()
{
    while (true)
    {
        auto& hostPlayer = playerLists[hostPlayerID];
        auto& clientPlayer = playerLists[clientPlayerID];

        unsigned int clientChoiceCard = mySocket->receivePlayerChoice();
        processPlayerTurn(clientPlayerID, clientChoiceCard, playerLists);
        onUiStateChange(Ui::WAITING_FOR_CONFIRMATION, playerLists, hostPlayerID, clientChoiceCard);

        unsigned int cardPlayed = hostPlayer.pickACardToPlay();
        mySocket->sendPlayerChoice(cardPlayed);
        processPlayerTurn(hostPlayerID, cardPlayed, playerLists);
        onUiStateChange(Ui::WAITING_FOR_NEXT_TURN, playerLists, hostPlayerID, clientChoiceCard);
        roundCount++;
    }
}

void Engine::processClientPlayerTurn()
{
    while (true)
    {
        auto& hostPlayer = playerLists[hostPlayerID];
        auto& clientPlayer = playerLists[clientPlayerID];

        unsigned int cardPlayed = clientPlayer.pickACardToPlay();

        mySocket->sendPlayerChoice(cardPlayed);
        processPlayerTurn(clientPlayerID, cardPlayed, playerLists);
        onUiStateChange(Ui::WAITING_FOR_NEXT_TURN, playerLists, clientPlayerID, cardPlayed);

        unsigned int serverChoiceCard = mySocket->receivePlayerChoice();
        processPlayerTurn(hostPlayerID, serverChoiceCard, playerLists);
        onUiStateChange(Ui::WAITING_FOR_CONFIRMATION, playerLists, hostPlayerID, serverChoiceCard);
    }
}

void Engine::processSinglePlayerTurn()
{
    unsigned int cardChoiced;

    while (true)
    {
        auto& currentPlayer = playerLists[currentTurn];
        auto& opponentPlayer = playerLists[nextTurn];
        unsigned int cardPlayed = currentPlayer.pickACardToPlay();
        processPlayerTurn(static_cast<PlayerId>(currentTurn), cardPlayed, playerLists);
        onUiStateChange(Ui::WAITING_FOR_CONFIRMATION, playerLists, static_cast<PlayerId>(currentTurn), cardPlayed);
        endTurnForPlayer();
    }
}

void Engine::processPlayerTurn(PlayerId playerID, unsigned int cardPlayed, std::vector<Player>& players)
{
    auto cardIterator = players[playerID].getHand().begin() + cardPlayed;

    for (size_t playerIndex = 0; playerIndex < MAX_PLAYER; playerIndex++)
    {
        if (isGameOver((PlayerId)playerIndex))
            onUiStateChange(Ui::DISPLAYING_RESULT, players, (PlayerId)(1-playerIndex), cardPlayed);
    }

    players[playerID].activeCardOnHand(players[playerID], players[1 - playerID], cardIterator);

    if (roundCount == 3)
    {
        players[playerID].drawCard(1);
        players[1 - playerID].drawCard(1);
        updatePlayerHandCard(players[playerID], players[1 - playerID]);
        roundCount = 0;
    }

    onUiStateChange(Ui::UPDATING_BATTLE, players, playerID, cardPlayed);

    for (size_t playerIndex = 0; playerIndex < MAX_PLAYER; playerIndex++)
    {
        players[playerIndex].stats.clear();
    }

    roundCount++;
}

void Engine::updatePlayerHandCard(Player& hostPlayer, Player& clientPlayer)
{
    switch (currentGameMode)
    {
        case MySocket::Mode::CLIENT:
            if (mySocket->recvInitCardPool(hostPlayer, clientPlayer))
            {
                onUiStateChange(Ui::UPDATING_HANDCARD, playerLists, clientPlayerID,
                                (unsigned int&)(currentGameMode));
            }
            break;

        case MySocket::Mode::HOST:
            if (mySocket->sendInitCardPool(hostPlayer, clientPlayer))
            {
                onUiStateChange(Ui::UPDATING_HANDCARD, playerLists, hostPlayerID,
                                (unsigned int&)(currentGameMode));
            }
            break;
    }
}

void Engine::registerUiModule(Ui* subUi)
{
    uiObs = subUi;
}

void Engine::onUiStateChange(Ui::UiState state, std::vector<Player>& players, PlayerId playerId, unsigned int& clone)
{
    uiObs->onUiStateChangeOnState(state, players, playerId, clone);
}

Engine::~Engine() {}
