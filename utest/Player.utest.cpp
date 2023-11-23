#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "Player/Player.h"
#include "UI/Ui.h"
#include "Hero/Hero.h"
#include "gmock/gmock.h"

class UiMock : public Ui
{
public:
    MOCK_METHOD(void, updateUiOnState, (UiState state, std::vector<Player> &players, unsigned int playerId, unsigned int &clone));
};

class PlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        uiMock = new UiMock();
        player1 = new Player(PlayerId::PLAYER_1, uiMock);
        player2 = new Player(PlayerId::PLAYER_2, uiMock);
    }

    void TearDown() override
    {
        delete player1;
        delete player2;
        delete uiMock;
    }

    UiMock *uiMock;
    Player *player1;
    Player *player2;
};
TEST_F(PlayerTest, TestGetId)
{
    EXPECT_EQ(player1->getId(), PlayerId::PLAYER_1);
    EXPECT_EQ(player2->getId(), PlayerId::PLAYER_2);
}

TEST_F(PlayerTest, TestDrawCard)
{
    unsigned int num = 3;
    player1->drawCard(num);
    std::vector<std::shared_ptr<Card>> &handCards = player1->getHand();
    EXPECT_EQ(handCards.size(), num);
}

TEST_F(PlayerTest, TestUpdateCard)
{
    player1->drawCard(1);
    std::vector<std::shared_ptr<Card>> &handCards = player1->getHand();
    CardType type = CardType::BRAWL;
    player1->updateCard(type);
    EXPECT_FALSE(handCards.empty());
    EXPECT_EQ(player1->getHand()[1]->getCardType(), CardType::BRAWL);
}

TEST_F(PlayerTest, TestGetHand)
{
    std::vector<std::shared_ptr<Card>> &handCards = player1->getHand();
    EXPECT_TRUE(handCards.empty());
}

TEST_F(PlayerTest, TestGetBattle)
{
    std::vector<std::shared_ptr<Card>> &battleCards = player1->getBattle();
    EXPECT_TRUE(battleCards.empty());
}

// TEST_F(PlayerTest, TestPickACardToPlay)
// {
//     // Expectations
//     player1->drawCard(10);
//     player2->drawCard(10);
//     EXPECT_CALL(*uiMock, updateUiOnState(testing::_, testing::_, testing::_, testing::_))
//         .WillOnce(testing::DoAll(testing::SetArgReferee<3>(2), testing::Return()));

//     // Assertion
//     EXPECT_EQ(player1->pickACardToPlay(), 2);
//     EXPECT_EQ(player2->pickACardToPlay(), 2);
// }

TEST_F(PlayerTest, TestActiveCardOnHand)
{
    player1->setHero(HeroType::BUTCHER);
    player2->setHero(HeroType::SLARK);
    player1->drawCard(1);
    std::vector<std::shared_ptr<Card>> &handCards1 = player1->getHand();
    std::vector<std::shared_ptr<Card>>::iterator cardPlayed = handCards1.begin();

    EXPECT_NO_FATAL_FAILURE(player1->activeCardOnHand(*player1, *player2, cardPlayed));
}

TEST_F(PlayerTest, TestSetHero)
{
    player1->setHero(HeroType::BUTCHER);
    EXPECT_EQ(player1->getHero()->getType(), HeroType::BUTCHER);
}

TEST_F(PlayerTest, TestGetBasicInfo)
{
    player1->setHero(HeroType::BUTCHER);
    EXPECT_EQ(player1->getBasicInfo(), "Player [1]'s Hero: Butcher HP[120] ATTACK [6]");
}

TEST_F(PlayerTest, TestGetHero)
{
    player1->setHero(HeroType::BUTCHER);
    std::shared_ptr<Hero> &hero = player1->getHero();
    EXPECT_EQ(hero->getType(), HeroType::BUTCHER);
}
