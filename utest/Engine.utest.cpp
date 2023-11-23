
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Engine/Engine.h"
#include "mock/mock_Ui.h"
#include "mock/mock_Engine.h"
#include "mock/mock_Player.h"
class MockUi : public Ui
{
public:
#define _ testing::_
    MOCK_METHOD(void, onUiStateChangeOnState, (Ui::UiState, std::vector<Player> &, PlayerId, unsigned int &), ());
};

class EngineTest : public ::testing::Test
{
protected:
    Player player1{PLAYER_1, nullptr};
    Player player2{PLAYER_2, nullptr};

    void SetUp() override
    {
        mockUi = std::make_unique<MockUi>();
        mockEngine = std::make_unique<Mock_Engine>(player1, player2, mockUi.get());
    }

    void TearDown() override
    {
        mockUi.reset();
        mockEngine.reset();
    }

    MockUi *getMockUi() const
    {
        return mockUi.get();
    }

    std::unique_ptr<MockUi> mockUi;
    std::unique_ptr<Mock_Engine> mockEngine;
};

TEST_F(EngineTest, InitializeOperationModeCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times(1);

    mockEngine->initializeOperationMode();
}

TEST_F(EngineTest, StartGameCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times((1));

    mockEngine->startGame();
}

TEST_F(EngineTest, ProcessHostPlayerTurnCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times((1));

    mockEngine->processHostPlayerTurn();
}

TEST_F(EngineTest, ProcessClientPlayerTurnCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times((1));

    mockEngine->processClientPlayerTurn();
}

TEST_F(EngineTest, ProcessSinglePlayerTurnCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times((1));

    mockEngine->processSinglePlayerTurn();
}

TEST_F(EngineTest, ProcessPlayerTurnCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times((1));

    // mockEngine->processPlayerTurn(PLAYER_1, 0, player1, player2);
}

TEST_F(EngineTest, UpdatePlayerHandCardCallsUiMethod)
{
    EXPECT_CALL(*getMockUi(), onUiStateChangeOnState(_, _, _, _)).Times((1));

    mockEngine->updatePlayerHandCard(player1, player2);
}

// TEST_F(EngineTest, EndTurnForPlayerSwapsTurns)
// {
//     PlayerId initialTurn = mockEngine->getCurrentTurn();
//     mockEngine->endTurnForPlayer();
//     PlayerId newTurn = mockEngine->getCurrentTurn();
//     EXPECT_NE(initialTurn, newTurn);
// }

// Add more tests for other methods, game states, and scenarios as needed...

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
