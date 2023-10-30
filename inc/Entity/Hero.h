#ifndef HERO_H
#define HERO_H

#include "Entity/Entity.h"
#include <vector>
#include <memory>

class Hero : public GameEntity
{
public:
    Hero() : GameEntity() {}
    Hero(std::string n, int a, int h, const std::string &sk, EntityType tp) : GameEntity(n, a, h, sk, tp) {}
    void InitHeroes();
    bool IsAlive();
    std::vector<std::shared_ptr<Hero>> &GetHeroes();

private:
    std::vector<std::shared_ptr<Hero>> heroes;
};
#endif