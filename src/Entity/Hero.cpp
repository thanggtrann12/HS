#include "Entity/Entity.h"
#include "Entity/Hero.h"
#include <iostream>
#include <algorithm>
#include "Helper/Helper.h"
void Hero::InitHeroes()
{
    LOG_I("Hero init: ");
    Hero butcher("Butcher", 6, 120, "Normal Attack", EntityType::HERO);
    LOG_D(butcher.GetDescription().c_str());
    heroes.push_back(std::make_shared<Hero>(butcher));
    Hero slark("Slark", 10, 72, "Normal Attack", EntityType::HERO);
    LOG_D(slark.GetDescription().c_str());
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