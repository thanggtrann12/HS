#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "UI/Ui.h"
#include "Player/Player.h"

class MockUi : public Ui
{
public:
    MOCK_METHOD(void, onUiStateChangeOnState, (Ui::UiState, std::vector<Player>&, PlayerId, unsigned int&), ());
};

class MockPlayer : public Player
{
public:
    MockPlayer(PlayerId playerId, Ui* ui) : Player(playerId, ui) {}

    MOCK_METHOD(void, drawCard, (unsigned int), ());
    MOCK_METHOD(void, updateCard, (CardType), ());
    MOCK_METHOD(unsigned int, pickACardToPlay, (), ());
    MOCK_METHOD(void, activeCardOnHand, (Player&, Player&, std::vector<std::shared_ptr<Card>>::iterator), ());
    MOCK_METHOD(void, setHero, (HeroType), ());
    MOCK_METHOD(std::string, getBasicInfo, (), ());
    MOCK_METHOD(std::shared_ptr<Hero>&, getHero, (), ());
    MOCK_METHOD(void, attackOpponent, (Player&), ());
};

class PlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockUi = std::make_unique<MockUi>();
    }

    void TearDown() override
    {

    }

    std::unique_ptr<MockUi> mockUi;
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
    unsigned int damage =  player_1.getHero()->getAttack();
    int hp_left = player_2.getHero()->getHP() - damage;
    player_1.getHero()->attackDefenderHero(player_2);
    EXPECT_EQ(player_2.getHero()->getHP(), hp_left);
}

