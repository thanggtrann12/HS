#ifndef MOCK_HERO_H
#define MOCK_HERO_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Hero/Hero.h"

// Mock class for Mock_Hero
class Mock_Hero : public Hero {
public:
    MOCK_METHOD(bool, IsAlive, ());
    MOCK_METHOD(void, attackDefenderHero, (Player &defender));
    MOCK_METHOD(void, takeDamage, (unsigned int damage));
    MOCK_METHOD(std::string, getDescription, ());
};
#endif // MOCK_HERO_H
