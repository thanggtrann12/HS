#ifndef MINION_H
#define MINION_H

#include "Units/Units.h"
#include <vector>
#include <memory>

class Minion : public Units
{
public:
    Minion(const std::string &name, int maxHP, int attack, CardType type)
        : Units(name, maxHP, attack, type) {}
};

class FlametongueTotem : public Minion
{
public:
    FlametongueTotem();

    void applyBuff(std::vector<std::shared_ptr<Minion>> &minions);
};

class RagnarosTheFirelord : public Minion
{
public:
    RagnarosTheFirelord();
};
class BloodmageThalnos : public Minion
{
public:
    BloodmageThalnos();
};
class Brawl : public Minion
{
public:
    Brawl();
};
class Techies : public Minion
{
public:
    Techies();
};
#endif // MINION_H
