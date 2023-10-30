#ifndef UNITS_H
#define UNITS_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
class Hero;
class GameEntity;

enum class EntityType
{
    MINION,
    BRAWL,
    TECHIES,
    SHAMAN,
    HERO
};

class GameEntity
{
public:
    GameEntity() : name("DefaultName"), attack(0), health(0), skill("DefaultSkill"), type(EntityType::HERO) {}
    GameEntity(std::string n, int a, int h, std::string sk, EntityType tp);
    std::string GetName() const;
    std::string GetSkill() const;
    int GetAttack() const;
    int GetHealth() const;
    bool IsAlive();
    EntityType GetEntitiesType() const;
    void TakeDamage(int damage);
    void AttackHero(std::shared_ptr<Hero> &hero, int damage);
    std::string GetDescription() const;
    void SetAttack(int _newAtk);
    bool IsUsed() const;
    void SetIsUsed(bool used);
    std::string EntityTypeToString(EntityType entityType);
    virtual ~GameEntity();

protected:
    std::string name;
    std::string skill;
    EntityType type;
    bool used;
    int attack;
    int health;
    int maxhealth;
};

#endif // UNITS_H
