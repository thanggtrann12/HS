#define GTEST_FRIEND \
FRIEND_TEST(EngineTest, SwapTurn); \
FRIEND_TEST(EngineTest, CheckUiObs);\
FRIEND_TEST(EngineTest, UpdateUiWithState);\

#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "Player/Player.h"
#include "Engine/Engine.h"
#include "UI/Ui.h"

// Mock for Ui class
class UiMock : public Ui
{
public:
    MOCK_METHOD(void, updateUiOnState, (UiState state, std::vector<Player> &players, unsigned int playerId, unsigned int &clone));
};

class EngineTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        uiMock = new UiMock();
        player1 = new Player(PlayerId::PLAYER_1, uiMock);
        player2 = new Player(PlayerId::PLAYER_2, uiMock);
        engine = new Engine(*player1, *player2, uiMock);
    }

    void TearDown() override
    {
        delete player1;
        delete player2;
        delete uiMock;
        delete engine;
    }

protected:
    UiMock *uiMock;
    Player *player1;
    Player *player2;
    Engine *engine;
};

// Tests for Engine class
TEST_F(EngineTest, SwapTurn)
{
    // Act
    player1->setHero(BUTCHER);
    player2->setHero(SLARK);
    engine->currentTurn = 1;
    engine->nextTurn = 2;
    engine->endTurn();

    // Assert
    EXPECT_EQ(engine->currentTurn, 2);
    EXPECT_EQ(engine->nextTurn, 1);
}
TEST_F(EngineTest, CheckUiObs)
{
   engine->addUiObserver(uiMock);
   EXPECT_TRUE(engine->uiObs);
}

TEST_F(EngineTest, UpdateUiWithState)
{
  EXPECT_CALL(*uiMock,updateUiOnState(::testing::_,::testing::_,::testing::_,::testing::_)).Times(1);
  std::vector<Player> players;
  unsigned int clone;
   engine->updateUi(Ui::UiState::INIT,players, PLAYER_1,  clone);
}


