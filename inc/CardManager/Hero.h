#ifndef HERO_H
#define HERO_H

#include <vector>
#include <memory>
#include "Helper/Helper.h"
class Hero
{
public:
    Hero() : name("Hero"), health(0), attack(0) {}
    Hero(std::string name, int atk, int hp) : name(name), health(hp), attack(atk) {}
    void initHero();
    bool IsAlive();
    std::vector<std::shared_ptr<Hero>> &getHero();
    void attackDefenderHero(GameData_t &defender);
    void getDamage(unsigned int damage);
    const std::string &getName() const { return name; }

private:
    std::vector<std::shared_ptr<Hero>> heroPocket;
    std::string name;
    int health;
    int attack;
};

#endif