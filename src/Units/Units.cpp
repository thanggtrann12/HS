#include "Units/Units.h"
#include <iostream>
Units::Units(const std::string &name, int maxHP, int attack, CardType type)
    : name(name), maxHP(maxHP), currentHP(maxHP), _attack(attack), cardType(type) {}

Units::~Units() {}

void Units::takeDamage(int damage)
{

    currentHP -= damage;
    if (currentHP < 0)
    {
        currentHP = 0;
    }
}

int Units::attack(Units *target)
{
    int damageDealt = _attack;
    target->takeDamage(damageDealt);
    return damageDealt;
}

bool Units::isAlive() const
{
    return currentHP > 0;
}

int Units::getAttack() const
{
    return _attack;
}
void Units::setAttack(int newAtk)
{
    _attack -= newAtk;
}

const std::string &Units::getName() const
{
    return name;
}

int Units::getCurrentHP() const
{
    return currentHP;
}

int Units::getMaxHp() const
{
    return maxHP;
}

int Units::getTotalDamage()
{
    int total = maxHP - currentHP;
    maxHP = currentHP;
    return total;
}

void Units::boostAttack(int boost)
{
    isActive = true;
    _attack += boost;
}
bool Units::isActivated()
{
    return isActive;
}
void Units::setActivated(bool state)
{
    isActive = state;
}
std::string Units::getDescription()
{
    return name + " HP [" + std::to_string(currentHP) + "] Attack [" + std::to_string(_attack) + "]";
}
CardType Units::getCardType() const
{
    return cardType;
}