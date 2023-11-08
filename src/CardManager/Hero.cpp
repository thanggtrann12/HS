#include "CardManager/Hero.h"
#include <iostream>
#include <algorithm>
#include "Helper/Helper.h"
void Hero::initHero()
{
    Hero butcher("Butcher", 6, 120);
    heroPocket.push_back(std::make_shared<Hero>(butcher));
    Hero slark("Slark", 10, 72);
    heroPocket.push_back(std::make_shared<Hero>(slark));
}

std::vector<std::shared_ptr<Hero>> &Hero::getHero()
{
    return heroPocket;
}
bool Hero::IsAlive()
{
    return health > 0;
}

void Hero::attackDefenderHero(GameData_t &defender)
{
    defender.hero->takeDamage(attack);
}

void Hero::takeDamage(unsigned int damage)
{
    health = (health > damage) ? health - damage : 0;
}