#include "gtest/gtest.h"
#include "Hero/Hero.h"
#include "Player/Player.h"

TEST(HeroTest, InitHero)
{
    Hero hero;
    hero.initHero();
    std::vector<std::shared_ptr<Hero>> heroPocket = hero.getHero();

    ASSERT_EQ(heroPocket.size(), 2);
    ASSERT_EQ(heroPocket[0]->getDescription(), "Butcher HP[120] ATTACK [6]");
    ASSERT_EQ(heroPocket[1]->getDescription(), "Slark HP[72] ATTACK [10]");
}

TEST(HeroTest, IsAlive)
{
    Hero hero;
    hero.initHero();

    ASSERT_TRUE(hero.getHero()[0]->IsAlive());
    ASSERT_TRUE(hero.getHero()[1]->IsAlive());

    hero.getHero()[1]->takeDamage(100);

    ASSERT_TRUE(hero.getHero()[0]->IsAlive());
    ASSERT_FALSE(hero.getHero()[1]->IsAlive());
}

TEST(HeroTest, AttackDefenderHero)
{
    Player Player_1(PLAYER_1, nullptr);
    Player_1.setHero(HeroType::BUTCHER);
    auto &attacker = Player_1.getHero();

    Player Player_2(PLAYER_2, nullptr);
    Player_2.setHero(HeroType::SLARK);
    auto &defender = Player_2.getHero();

    ASSERT_EQ(attacker->getDescription(), "Butcher HP[120] ATTACK [6]");
    ASSERT_EQ(defender->getDescription(), "Slark HP[72] ATTACK [10]");

    attacker->attackDefenderHero(Player_2);

    ASSERT_EQ(attacker->getDescription(), "Butcher HP[120] ATTACK [6]");
    ASSERT_EQ(defender->getDescription(), "Slark HP[66] ATTACK [10]");
}

TEST(HeroTest, TakeDamage)
{
    Hero hero;
    hero.initHero();

    ASSERT_EQ(hero.getHero()[0]->getDescription(), "Butcher HP[120] ATTACK [6]");
    ASSERT_EQ(hero.getHero()[1]->getDescription(), "Slark HP[72] ATTACK [10]");

    hero.getHero()[0]->takeDamage(50);
    hero.getHero()[1]->takeDamage(150);

    ASSERT_EQ(hero.getHero()[0]->getDescription(), "Butcher HP[70] ATTACK [6]");
    ASSERT_EQ(hero.getHero()[1]->getDescription(), "Slark HP[0] ATTACK [10]");
}

TEST(HeroTest, GetDescription)
{
    Hero hero;
    hero.initHero();

    ASSERT_EQ(hero.getHero()[0]->getDescription(), "Butcher HP[120] ATTACK [6]");
    ASSERT_EQ(hero.getHero()[1]->getDescription(), "Slark HP[72] ATTACK [10]");
}