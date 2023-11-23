#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "UI/Ui.h"

#include "Player/Player.h"
class Mock_Ui : public Ui {
public:
    MOCK_METHOD(void, displayMenuScreen, (unsigned int &choicedMode));
    MOCK_METHOD(void, selectCard, (Player &player, unsigned int &choicedCard));
    MOCK_METHOD(void, displayPlayerCard, (Player &player, unsigned int &choicedCard));
    MOCK_METHOD(void, displayCardList, (std::vector<std::shared_ptr<Card>> &playerHandCard, int currentIndex));
    MOCK_METHOD(void, displayBattle, (std::vector<Player> &players, unsigned int playerId));
    MOCK_METHOD(void, displayResult, (Player &player));
    MOCK_METHOD(void, updateUiOnState, (UiState state, std::vector<Player> &players, unsigned int playerId, unsigned int &clone));
};
class UiTest : public testing::Test {
protected:
    Mock_Ui mockUi;  // Mock object to be used in tests
};

TEST_F(UiTest, DisplayMenuScreen) {
    unsigned int choice;

    // Expectations for the mock method
    EXPECT_CALL(mockUi, displayMenuScreen(testing::_))
        .WillOnce(testing::SetArgReferee<0>(1));  // Set the choice to 1
    mockUi.displayMenuScreen(choice);
    // Check if the choice is updated correctly
    EXPECT_EQ(choice, 1);
}

TEST_F(UiTest, SelectCard) {
    unsigned int choice;
    Player player;

    // Expectations for the mock method
    EXPECT_CALL(mockUi, selectCard(testing::_, testing::_))
        .WillOnce(testing::SetArgReferee<1>(2));  // Set the choice to 2

    mockUi.selectCard(player, choice);

    // Check if the choice is updated correctly
    EXPECT_EQ(choice, 2);
}

TEST_F(UiTest, DisplayPlayerCard) {
    unsigned int choice;
    Player player;

    EXPECT_CALL(mockUi, displayPlayerCard(testing::_, testing::_))
        .WillOnce(testing::SetArgReferee<1>(3));

    mockUi.displayPlayerCard(player, choice);
    EXPECT_EQ(choice, 3);
}

TEST_F(UiTest, DisplayCardList) {
    std::vector<std::shared_ptr<Card>> playerHand;
    int currentIndex;

    EXPECT_CALL(mockUi, displayCardList(testing::_, testing::_));

    mockUi.displayCardList(playerHand, currentIndex);
}

TEST_F(UiTest, DisplayBattle) {
    std::vector<Player> players;
    unsigned int playerId;

    EXPECT_CALL(mockUi, displayBattle(testing::_, testing::_));

    mockUi.displayBattle(players, playerId);
}

TEST_F(UiTest, DisplayResult) {
    Player player;
    EXPECT_CALL(mockUi, displayResult(testing::_));

    mockUi.displayResult(player);
}

TEST_F(UiTest, UpdateUiOnState) {
    Ui::UiState state;
    std::vector<Player> players;
    unsigned int playerId;
    unsigned int clone;

    EXPECT_CALL(mockUi, updateUiOnState(testing::_, testing::_, testing::_, testing::_));

    mockUi.updateUiOnState(state, players, playerId, clone);
}

