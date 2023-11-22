#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "UI/Ui.h"
#include "Player/Player.h"
#include "mock/mock_Ui.h"
#include "mock/mock_Player.h"
#define _ testing::_

class PlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockUi = std::make_unique<Mock_Ui>();
    }

    void TearDown() override
    {
    }

    std::unique_ptr<Mock_Ui> mockUi;
};

TEST_F(PlayerTest, DrawCardIncreasesHandSize)
{
    Player player(PLAYER_1, mockUi.get());
    unsigned int initialHandSize = player.getHand().size();
    unsigned int numCardsToDraw = 2;

    player.drawCard(numCardsToDraw);

    EXPECT_EQ(player.getHand().size(), initialHandSize + numCardsToDraw);
}

TEST_F(PlayerTest, SetHeroAssignsHeroType)
{
    Player player(PLAYER_1, mockUi.get());
    HeroType heroType = SLARK;

    player.setHero(heroType);

    EXPECT_EQ(player.getHero()->getType(), heroType);
}

TEST_F(PlayerTest, AttackOpponentHero)
{
    Player player_1(PLAYER_1, mockUi.get());
    Player player_2(PLAYER_2, mockUi.get());
    player_1.setHero(BUTCHER);
    player_2.setHero(SLARK);

    unsigned int initialHP = player_2.getHero()->getHP();
    unsigned int damage = player_1.getHero()->getAttack();

    player_1.attackOpponent(player_2);

    EXPECT_EQ(player_2.getHero()->getHP(), initialHP - damage);
}

TEST_F(PlayerTest, UpdateCardUpdatesLastCardInHand)
{
    Player player(PLAYER_1, mockUi.get());
    CardType cardType = BRAWL;
    unsigned int handSize = 3;
    player.drawCard(handSize);

    CardType initialCardType = player.getHand().back()->getCardType();

    player.updateCard(cardType);

    CardType updatedCardType = player.getHand().back()->getCardType();

    EXPECT_NE(initialCardType, updatedCardType);
    EXPECT_EQ(updatedCardType, cardType);
}

TEST_F(PlayerTest, ActiveCardOnHand)
{
    Player player_1(PLAYER_1, mockUi.get());
    Player player_2(PLAYER_2, mockUi.get());
    player_1.setHero(BUTCHER);
    player_2.setHero(SLARK);
    player_2.updateCard(THALNOS);
    unsigned int initialHP = player_1.getHero()->getHP();
    unsigned int damage = player_2.getHero()->getAttack();
    player_2.attackOpponent(player_1);
    player_2.getHand()[player_2.getHand().size() - 1]->play(PLAYER_2, player_2, player_1);

    EXPECT_EQ(player_1.getHero()->getHP(), initialHP - damage - player_2.getHand()[player_2.getHand().size() - 1]->getAttack());
}

TEST_F(PlayerTest, GetBasicInfoReturnsNonEmptyString)
{
    Player player(PLAYER_1, mockUi.get());
    player.setHero(BUTCHER);
    std::string basicInfo = player.getBasicInfo();
    EXPECT_FALSE(basicInfo.empty());
}

TEST_F(PlayerTest, GetHeroReturnsNonNullPointer)
{
    Player player(PLAYER_1, mockUi.get());
    player.setHero(BUTCHER);
    std::shared_ptr<Hero> hero = player.getHero();

    EXPECT_NE(hero, nullptr);
}
