#include <gtest/gtest.h>
#include "CardManager/Hero.h"

class HeroTest : public ::testing::Test {
protected:
    Hero hero;
    void SetUp() override {
        hero.initHero();
    }

    void TearDown() override {
        hero.getHero().clear();
    }
};

TEST_F(HeroTest, InitHeroTest) {
    ASSERT_EQ(hero.getHero().size(), 2);
}

TEST_F(HeroTest, IsAliveTest) {
    GameData_t gameData;
    auto &attacker = hero.getHero()[0];
    ASSERT_TRUE(attacker->IsAlive());

    attacker->takeDamage(attacker->getHP());
    ASSERT_FALSE(attacker->IsAlive());
}


TEST_F(HeroTest, AttackDefenderHeroTest) {
    GameData_t gameData;
    auto &attacker = hero.getHero()[1];
    auto &defender = hero.getHero()[0];
    gameData.hero = defender;

    // Assuming the default attack is greater than 0
    unsigned int initialDefenderHealth = defender->getHP();
    attacker->attackDefenderHero(gameData);
    ASSERT_EQ(defender->getHP(), initialDefenderHealth -  attacker->getAttack());
}

TEST_F(HeroTest, TakeDamageTest) {
    GameData_t gameData;
    auto &attacker = hero.getHero()[0];
    unsigned int initialHealth = attacker->getHP();
    attacker->takeDamage(10);
    ASSERT_EQ(attacker->getHP(), initialHealth - 10);

    attacker->takeDamage(attacker->getHP());
    ASSERT_EQ(attacker->getHP(), 0);
}
