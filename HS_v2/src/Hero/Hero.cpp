#include "Hero/Hero.h"
#include <iostream>
#include <algorithm>
#include "Player/Player.h"
void Hero::initHero()
{
    Hero butcher(BUTCHER);
    heroPocket.push_back(std::make_shared<Hero>(butcher));
    Hero slark(SLARK);
    heroPocket.push_back(std::make_shared<Hero>(slark));
}

std::vector<std::shared_ptr<Hero>> &Hero::getHero()
{
    return heroPocket;
}
bool Hero::IsAlive()
{
    return heroData.health > 0;
}

void Hero::attackDefenderHero(Player &defender)
{
    defender.getHero()->takeDamage(heroData.attack);
}

void Hero::takeDamage(unsigned int damage)
{
    heroData.health = (heroData.health > damage) ? heroData.health - damage : 0;
}

std::string Hero::getDescription()
{
    return heroData.name + " HP[" + std::to_string(heroData.health) + "] ATTACK [" + std::to_string(heroData.attack) + "]";
}