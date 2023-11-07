#include "CardManager/GameEntities/Hero.h"
#include <iostream>
#include <algorithm>
#include "Helper/Helper.h"
void Hero::InitHeroes()
{
    Hero butcher("Butcher", 6, 120);
    heroes.push_back(std::make_shared<Hero>(butcher));
    Hero slark("Slark", 10, 72);
    heroes.push_back(std::make_shared<Hero>(slark));
}

std::vector<std::shared_ptr<Hero>> &Hero::GetHeroes()
{
    return heroes;
}
bool Hero::IsAlive()
{
    return health > 0;
}

void Hero::Hero_attackDefenderHero(GameData_t &defender)
{
    defender.hero->Hero_getDamage(attack);
}

void Hero::Hero_getDamage(unsigned int damage)
{
    health = (health > damage) ? health - damage : 0;
}