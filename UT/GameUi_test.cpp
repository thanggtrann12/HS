#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock/mock.h"
class GameUiTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Your common setup code here if needed
    }

    void TearDown() override
    {
        // Your common teardown code here if needed
    }
};
TEST(GameUiTest, UpdateGameStateTest_INIT)
{
    MockGameUi mockUi;
    int cardChoiced = 42;
    std::vector<GameData_t> tableData;

    // Set up expectations
    EXPECT_CALL(mockUi, GameUi_updateGameState(PLAYER_1, GameUi::INIT, cardChoiced, _)).Times(1);

    // Call the method under test
    mockUi.GameUi_updateGameState(PLAYER_1, GameUi::INIT, cardChoiced, tableData);
    EXPECT_CALL(mockUi, GameUi_displayModesOption(cardChoiced));
    mockUi.GameUi_displayModesOption(cardChoiced);
}
TEST(GameUiTest, UpdateGameStateTest_CHOICE)
{
    MockGameUi mockUi;
    int cardChoiced = 42;
    std::vector<GameData_t> tableData(MAX_PLAYER);

    EXPECT_CALL(mockUi, GameUi_updateGameState(PLAYER_1, GameUi::CHOICE, cardChoiced, _)).Times(1);
    mockUi.GameUi_updateGameState(PLAYER_1, GameUi::CHOICE, cardChoiced, tableData);
    EXPECT_CALL(mockUi, GameUi_displayHandCard(cardChoiced, _, tableData[PLAYER_1].handCard));
    mockUi.GameUi_displayHandCard(cardChoiced, " ", tableData[PLAYER_1].handCard);
}
TEST(GameUiTest, UpdateGameStateTest_STATS)
{
    MockGameUi mockUi;
    int cardChoiced = 42;
    std::vector<GameData_t> tableData(MAX_PLAYER);

    // Set up expectations
    EXPECT_CALL(mockUi, GameUi_updateGameState(PLAYER_1, GameUi::STATS, cardChoiced, _)).Times(1);
    mockUi.GameUi_updateGameState(PLAYER_1, GameUi::STATS, cardChoiced, tableData);
    EXPECT_CALL(mockUi, GameUi_prepareConsole()).Times(1);
    mockUi.GameUi_prepareConsole();
    EXPECT_CALL(mockUi, GameUi_displayEntireTable(_)).Times(1);
    mockUi.GameUi_displayEntireTable(tableData);
}
TEST(GameUiTest, UpdateGameStateTest_WAIT_CONFIRM)
{
    MockGameUi mockUi;
    int cardChoiced = 42;
    std::vector<GameData_t> tableData;

    // Set up expectations
    EXPECT_CALL(mockUi, GameUi_updateGameState(PLAYER_1, GameUi::WAIT_CONFIRM, cardChoiced, _)).Times(1);
    mockUi.GameUi_updateGameState(PLAYER_1, GameUi::WAIT_CONFIRM, cardChoiced, tableData);
    EXPECT_CALL(mockUi, GameUi_waitForConfirm()).Times(1);
    mockUi.GameUi_waitForConfirm();
}
TEST(GameUiTest, UpdateGameStateTest_WAIT_NEXT_TURN)
{
    MockGameUi mockUi;
    int cardChoiced = 42;
    std::vector<GameData_t> tableData;

    EXPECT_CALL(mockUi, GameUi_updateGameState(PLAYER_1, GameUi::WAIT_NEXT_TURN, cardChoiced, _)).Times(1);
    mockUi.GameUi_updateGameState(PLAYER_1, GameUi::WAIT_NEXT_TURN, cardChoiced, tableData);
    EXPECT_CALL(mockUi, GameUi_waitForNextTurn()).Times(1);
    mockUi.GameUi_waitForNextTurn();
}
TEST(GameUiTest, UpdateGameStateTest_RESULT)
{
    MockGameUi mockUi;
    int cardChoiced = 42;
    std::vector<GameData_t> tableData;

    // Set up expectations
    EXPECT_CALL(mockUi, GameUi_updateGameState(PLAYER_1, GameUi::RESULT, cardChoiced, _)).Times(1);
    mockUi.GameUi_updateGameState(PLAYER_1, GameUi::RESULT, cardChoiced, tableData);
    EXPECT_CALL(mockUi, GameUi_displayResult(_)).Times(1);
    mockUi.GameUi_displayResult(tableData);
}
