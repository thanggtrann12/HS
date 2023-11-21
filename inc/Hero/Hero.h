#ifndef HERO_H
#define HERO_H

#include <vector>
#include <memory>
#include "assets/HeroData.h"
#include "assets/CardData.h"
class Player;
class Hero
{
public:
    Hero() : heroData(heroes[BUTCHER]) {}
    Hero(HeroType type) : heroData(heroes[type]) {}

    void initHero();
    bool IsAlive();
    std::vector<std::shared_ptr<Hero>> &getHero();
    void attackDefenderHero(Player &defender);
    void takeDamage(unsigned int damage);
    const std::string &getName() const { return heroData.name; }
    const HeroType getType() const { return heroData.type; }
    int getHP() const { return heroData.health; }
    int getAttack() const { return heroData.attack; }
    std::string getDescription();

private:
    HeroData heroData;
    std::vector<std::shared_ptr<Hero>> heroPocket;
};

#endif