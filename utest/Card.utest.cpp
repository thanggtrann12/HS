#include <gtest/gtest.h>
#include "Card/Card.h"
#include "Card/CardFactory.h"
#include "Player/Player.h"

TEST(MinionCardTest, PlayTestEmptyBattle)
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

TEST(MinionCardTest, PlayTestRemoveTechies)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    attacker.shamanCout = 3;
    defender.setHero(SLARK);
    defender.updateCard(CardType::TECHIES);
    defender.getBattle().push_back(defender.getHand()[0]);
    MinionCard card(CardType::FIRELORD);
    card.play(1, attacker, defender);
    ASSERT_EQ(defender.getHero()->getHP() , 63); // DAMAGE FROM TECHIES(3) + MINION(FIRELORD = 3) WITH SHAMAN BUFF (3)
    ASSERT_EQ(attacker.getHero()->getHP() , 117);
}

TEST(MinionCardTest, PlayTestRemoveNotTechies)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    attacker.shamanCout = 3;
    defender.setHero(SLARK);
    defender.updateCard(CardType::SHAMAN);
    defender.getBattle().push_back(defender.getHand()[0]);
    MinionCard card(CardType::FIRELORD);
    card.play(1, attacker, defender);
    ASSERT_EQ(defender.getHero()->getHP() , 66); //MINION WITH SHAMAN BUFF
    ASSERT_EQ(attacker.getHero()->getHP() , 120);
}

TEST(MinionCardTest, PlayTestRemoveShaman)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    defender.shamanCout = 1;
    defender.setHero(SLARK);
    defender.updateCard(CardType::SHAMAN);
    defender.getBattle().push_back(defender.getHand()[0]);
    MinionCard card(CardType::FIRELORD);
    card.play(1, attacker, defender);
    ASSERT_EQ(defender.shamanCout , 0);
}

TEST(MinionCardTest, PlayTestDealDamageToCard)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    defender.shamanCout = 1;
    defender.setHero(SLARK);
    defender.updateCard(CardType::SHAMAN);
    defender.getBattle().push_back(defender.getHand()[0]);
    MinionCard card(CardType::THALNOS);
    card.play(1, attacker, defender);
    ASSERT_EQ(defender.getBattle()[0]->getHP() , 2);
}

TEST(MinionCardTest, GetDescriptionTest)
{
    MinionCard card(CardType::FIRELORD);
    std::string description = card.getDesciption();
    EXPECT_EQ(description, "Ragnaros the Firelord HP[1] ATK[3]");
}

TEST(BuffCardTest, PlayTestWithResetDamage)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    BuffCard card(CardType::SHAMAN);
    attacker.updateCard(CardType::FIRELORD);
    for (auto &e : attacker.getHand())
    {
      attacker.getBattle().push_back(e);
    }
    card.play(1, attacker, defender);
    EXPECT_EQ(attacker.getBattle()[0]->getAttack(), 3);

}

TEST(BuffCardTest, PlayTestCountShaman)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    attacker.shamanCout = 0;
    BuffCard card(CardType::SHAMAN);
    int totalExpectShamanCount = 3;
    attacker.updateCard(CardType::SHAMAN);
    for (int i =0; i<totalExpectShamanCount; i++)
    {
      attacker.getBattle().push_back(attacker.getHand()[0]);
    }
    card.play(0, attacker, defender);
    EXPECT_EQ(attacker.shamanCout, totalExpectShamanCount);

}

TEST(BuffCardTest, GetDescriptionTest)
{
    BuffCard card(CardType::SHAMAN);
    std::string description = card.getDesciption();
    EXPECT_EQ(description, "Flametongue Totem Provides all alliance  minions with a +1 Attack bonus. ACTIVE");
}

TEST(SpellCardTest, PlayTestEmptyCard)
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
TEST(SpellCardTest, PlayTestRemoveRandomNotTechies)
{
    // Create players and set up heroes
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    defender.setHero(SLARK);
    defender.drawCard(5);
    SpellCard card(CardType::BRAWL);

    for (auto &card : defender.getHand())
    {
      defender.getBattle().push_back(card);
    }
    card.play(0, attacker, defender);
    ASSERT_EQ(defender.getBattle().size(), 4);
}
TEST(SpellCardTest, PlayTestRemoveRandomIsTechies)
{
    // Create players and set up heroes
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    defender.setHero(SLARK);
    defender.updateCard(CardType::TECHIES);
    SpellCard card(CardType::BRAWL);

    for (auto &card : defender.getHand())
    {
      defender.getBattle().push_back(card);
    }
    card.play(0, attacker, defender);
    ASSERT_EQ(defender.getBattle().size(),0);
    /* both hero got 3 damage when techies eliminated*/
    ASSERT_EQ(defender.getHero()->getHP() , 69);
    ASSERT_EQ(attacker.getHero()->getHP() , 117);

}

TEST(SpellCardTest, GetDescriptionTest)
{
    SpellCard card(CardType::BRAWL);
    std::string description = card.getDesciption();
    EXPECT_EQ(description, "Brawl Destroy a random minion of the opposite player");
}

TEST(CardTest, TakeDamage)
{
    Player attacker(PLAYER_1, nullptr);
    Player defender(PLAYER_2, nullptr);
    attacker.setHero(BUTCHER);
    defender.setHero(SLARK);
    MinionCard card(CardType::TECHIES);
    card.takeDamage(10);

    EXPECT_EQ(card.getHP(), 0);
}