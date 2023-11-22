#include "Hero/Hero.h"
#include <iostream>
#include <algorithm>
#include "Player/Player.h"
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