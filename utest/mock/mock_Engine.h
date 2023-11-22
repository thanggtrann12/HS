#ifndef MOCK_ENGINE_H
#define MOCK_ENGINE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Engine/Engine.h"

// Mock class for Mock_Engine
class Mock_Engine : public Engine {
public:
    MOCK_METHOD(void, startGame, ());
    MOCK_METHOD(bool, isGameOver, (PlayerId playerID));
    MOCK_METHOD(void, initializeOperationMode, ());
    MOCK_METHOD(void, endTurnForPlayer, ());
    MOCK_METHOD(void, processPlayerTurn, (PlayerId playerID, unsigned int cardPlayed, std::vector<Player> &players));
    MOCK_METHOD(void, updatePlayerHandCard, (Player &hostPlayer, Player &clientPlayer));
    MOCK_METHOD(void, processHostPlayerTurn, ());
    MOCK_METHOD(void, processClientPlayerTurn, ());
    MOCK_METHOD(void, processSinglePlayerTurn, ());
    MOCK_METHOD(void, registerUiModule, (Ui *subUi));
    MOCK_METHOD(void, onUiStateChange, (Ui::UiState state, std::vector<Player> &players, PlayerId playerId, unsigned int &clone));
};
#endif // MOCK_ENGINE_H
