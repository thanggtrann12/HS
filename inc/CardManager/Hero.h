#ifndef HERO_H
#define HERO_H

#include <vector>
#include <memory>
#include "Helper/Helper.h"
#include "CardFactory/CardData.h"
class Hero
{
public:
    Hero() : name("Hero"), health(0), attack(0) {}
    Hero(CardType type) : name(cardDatas[type].name), health(cardDatas[type].health), attack(cardDatas[type].attack) {}
    void initHero();
    bool IsAlive();
    std::vector<std::shared_ptr<Hero>> &getHero();
    void attackDefenderHero(GameData_t &defender);
    void takeDamage(unsigned int damage);
    const std::string &getName() const { return name; }
    int getHP() const { return health; }
    int getAttack() const { return attack; }

private:
    std::vector<std::shared_ptr<Hero>> heroPocket;
    std::string name;
    int health;
    int attack;
};

#endif