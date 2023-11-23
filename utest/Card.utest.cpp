#include <gtest/gtest.h>
#include "Card/Card.h"
#include "Card/CardFactory.h"
#include "Player/Player.h"

TEST(MinionCardTest, PlayTest)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    attacker.shamanCout = 3;
    defender.setHero(SLARK);
    MinionCard card(CardType::FIRELORD);
    unsigned int attackBeforeBuff = card.getAttack() + attacker.shamanCout;
    unsigned int hpBeforeAtk = defender.getHero()->getHP();
    card.play(1, attacker, defender);
    EXPECT_EQ(card.getAttack(), attackBeforeBuff);
    EXPECT_EQ(defender.getHero()->getHP(), hpBeforeAtk - card.getAttack());
}

TEST(MinionCardTest, GetDescriptionTest)
{
    MinionCard card(CardType::FIRELORD);
    std::string description = card.getDesciption();
    EXPECT_EQ(description, "Ragnaros the Firelord HP[1] ATK[3]");
}

TEST(BuffCardTest, PlayTest)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    attacker.shamanCout = 3;
    defender.setHero(SLARK);
    BuffCard card(CardType::SHAMAN);
    attacker.drawCard(1);
    card.play(1, attacker, defender);
    attacker.getHand()[0]->play(1, attacker, defender);
    EXPECT_EQ(attacker.getHand()[0]->getAttack(), 3);
}

TEST(BuffCardTest, GetDescriptionTest)
{
    BuffCard card(CardType::SHAMAN);
    std::string description = card.getDesciption();
    EXPECT_EQ(description, "Flametongue Totem Provides all alliance  minions with a +1 Attack bonus. ACTIVE");
}

TEST(SpellCardTest, PlayTest)
{
    // Create players and set up heroes
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    defender.setHero(SLARK);

    // Create a SpellCard
    SpellCard card(CardType::SHAMAN);

    // Play the SpellCard
    card.play(1, attacker, defender);

    ASSERT_EQ(attacker.stats.size(), 2);
    EXPECT_EQ(attacker.stats[0], "Player [1] active Flametongue Totem Provides all alliance  minions with a +1 Attack bonus.");
    EXPECT_EQ(attacker.stats[1], "Player [1] attack Player [2] with 6 damage");

    ASSERT_EQ(defender.stats.size(), 1);
    EXPECT_EQ(defender.stats[0], "Player [2] had no card on table");
}

TEST(SpellCardTest, GetDescriptionTest)
{
    SpellCard card(CardType::BRAWL);
    std::string description = card.getDesciption();
    EXPECT_EQ(description, "Brawl Destroy a random minion of the opposite player");
}
