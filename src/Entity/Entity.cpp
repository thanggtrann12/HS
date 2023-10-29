#include "Entity/Entity.h"
#include <iostream>
GameEntity::GameEntity(std::string n, int a, int h, std::string sk, EntityType tp)
    : name(n), attack(a), health(h), skill(sk), type(tp) { maxhealth = health; }

std::string GameEntity::GetName() const
{
    return name;
}
int GameEntity::GetAttack() const
{
    return attack;
}
int GameEntity::GetHealth() const
{
    return health;
}
bool GameEntity::IsAlive()
{
    return health > 0;
}
EntityType GameEntity::GetEntitiesType() const
{
    return type;
}

void GameEntity::TakeDamage(int damage)
{
    health = health > 0 ? health -= damage : 0;
    maxhealth = health;
}
void GameEntity::AttackHero(std::shared_ptr<Hero> &hero, int damage)
{
    hero->TakeDamage(damage);
}
std::string GameEntity::GetDescription() const
{

    return name + ": HP[" + std::to_string(health) + "] - ATTACK[" + std::to_string(attack) + "] - " + "[" + (used == true ? "ACTIVE] " : "INACTIVE] " + skill);
}
void GameEntity::SetAttack(int _newAtk)
{
    attack += _newAtk;
}
bool GameEntity::IsUsed() const
{
    return used;
}
void GameEntity::SetIsUsed(bool use)
{
    used = use;
}

GameEntity::~GameEntity() {}