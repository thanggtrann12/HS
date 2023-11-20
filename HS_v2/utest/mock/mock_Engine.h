#ifndef MOCK_ENGINE_H
#define MOCK_ENGINE_H

 #include "gtest/gtest.h"
 #include "gmock/gmock.h"
#include "Engine/Engine.h"

// Mock class for Mock_Engine
class Mock_Engine : public Engine {
public:
    MOCK_METHOD(void, startGame, ());
    MOCK_METHOD(bool, isEndGame, (PlayerId playerID));
    MOCK_METHOD(int, getTurn, ());
    MOCK_METHOD(void, endTurn, ());
    MOCK_METHOD(void, handlingPlayerTurn, (PlayerId playerID, unsigned int cardPlayed, std::vector<Player> &players));
    MOCK_METHOD(void, generateCardsForEachMode, (MySocket *host, Player &hostPlayer, MySocket *client, Player &clientPlayer));
    MOCK_METHOD(void, startHostMode, (MySocket *host));
    MOCK_METHOD(void, startClientMode, (MySocket *client));
    MOCK_METHOD(void, startSingleMode, ());
    MOCK_METHOD(void, addUiObserver, (Ui *subUi));
    MOCK_METHOD(void, updateUi, (Ui::UiState state, std::vector<Player> &players, PlayerId playerId, unsigned int &clone));
};
#endif // MOCK_ENGINE_H
