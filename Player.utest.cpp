#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Player/Player.h"
#include "mock/mock_Player.h"
#include "mock/mock_Card.h"
#include "Card/Card.h"
using ::testing::Return;
using ::testing::_;

// Test fixture for Player class
class PlayerTest : public testing::Test {
protected:
    Mock_Player mockPlayer;  // Mock object to be used in tests
};

TEST_F(PlayerTest, DrawCard) {
    EXPECT_CALL(mockPlayer, drawCard(_));

    mockPlayer.drawCard(3);
}

TEST_F(PlayerTest, UpdateCard) {
    EXPECT_CALL(mockPlayer, updateCard(CardType::BRAWL));
    mockPlayer.updateCard(CardType::BRAWL);
}


TEST_F(PlayerTest, PickACardToPlay) {
    EXPECT_CALL(mockPlayer, pickACardToPlay())
        .WillOnce(Return(42));

    unsigned int result = mockPlayer.pickACardToPlay();
    EXPECT_EQ(result, 42);
}

TEST_F(PlayerTest, AddCardToBattle) {
    EXPECT_CALL(mockPlayer, addCardToBattle(_));

    mockPlayer.addCardToBattle(mockPlayer.getHand().begin());
}

TEST_F(PlayerTest, SetHero) {
    EXPECT_CALL(mockPlayer, setHero(_));

    mockPlayer.setHero(HeroType::BUTCHER);
}

TEST_F(PlayerTest, GetBasicInfo) {
    EXPECT_CALL(mockPlayer, getBasicInfo())
        .WillOnce(Return("Mocked Player Info"));

    std::string result = mockPlayer.getBasicInfo();
    EXPECT_EQ(result, "Mocked Player Info");
}

TEST_F(PlayerTest, SetId) {
    EXPECT_CALL(mockPlayer, setId(_));
    mockPlayer.setId(PlayerId::PLAYER_1);
}

TEST_F(PlayerTest, GetId) {
    PlayerId id = mockPlayer.getId();
    EXPECT_EQ(id, PlayerId::PLAYER_1);
}

TEST_F(PlayerTest, GetHand) {
    EXPECT_CALL(mockPlayer, getHand());
    mockPlayer.getHand();
}

TEST_F(PlayerTest, GetBattle) {
    EXPECT_CALL(mockPlayer, getBattle());
    mockPlayer.getBattle();
}
