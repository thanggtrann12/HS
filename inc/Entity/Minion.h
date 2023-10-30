#ifndef MINION_H
#define MINION_H

#include "Game/GameData.h"
#include "Entity/Entity.h"
#include <vector>
#include <memory>

class Minion : public GameEntity
{
public:
    Minion(std::string n, int a, int h, std::string sk, EntityType tp)
        : GameEntity(n, a, h, sk, tp) {}
    virtual void applyEffect(std::vector<GameData_t> &player, int playerIndex) = 0;
    void DameToAllEntities(GameData_t &player, int damage);
    int shamanCnt;
};

class FlametongueTotem : public Minion
{
public:
    FlametongueTotem()
        : Minion("Flametongue Totem", 0, 3, "Provides 1 Attack to alliance minions", EntityType::SHAMAN) { SetIsUsed(false); };
    void applyEffect(std::vector<GameData_t> &player, int playerIndex) override;

private:
    const int shamanbuff = 1;
};

class RagnarosTheFirelord : public Minion
{
public:
    RagnarosTheFirelord()
        : Minion("Ragnaros the Firelord", 3, 1, "Normal Attack", EntityType::MINION) { SetIsUsed(false); };
    void applyEffect(std::vector<GameData_t> &player, int playerIndex) override;
};
class BloodmageThalnos : public Minion
{
public:
    BloodmageThalnos()
        : Minion("Bloodmage Thalnos", 1, 1, "Normal Attack", EntityType::MINION) { SetIsUsed(false); };
    void applyEffect(std::vector<GameData_t> &player, int playerIndex) override;
};
class Brawl : public Minion
{
public:
    Brawl()
        : Minion("Brawl", 0, 0, "Destroy a random minion of the opposite player", EntityType::BRAWL) { SetIsUsed(false); };
    void applyEffect(std::vector<GameData_t> &player, int playerIndex) override;
};
class Techies : public Minion
{
public:
    Techies()
        : Minion("Techies", 1, 2, "On dead it deals 3 damage to both hero", EntityType::TECHIES) { SetIsUsed(false); };
    void applyEffect(std::vector<GameData_t> &player, int playerIndex) override;
};
#endif // MINION_H
