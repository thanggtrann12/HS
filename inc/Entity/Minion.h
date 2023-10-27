#ifndef MINION_H
#define MINION_H

#include "Entity/Entity.h"
#include <vector>
#include <memory>
#define UNUSED(x) (void)(x)
class Minion : public GameEntity
{
public:
  Minion(std::string n, int a, int h, std::string sk, EntityType tp)
      : GameEntity(n, a, h, sk, tp) {}
  int shamanCnt;
};

class FlametongueTotem : public Minion
{
public:
  FlametongueTotem()
      : Minion("Flametongue Totem", 0, 3, "Provides +1 Attack to adjacent minions", EntityType::MINION){};
  void applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex) override;
  std::shared_ptr<GameEntity> createInstance() override
  {
    return std::make_shared<FlametongueTotem>();
  }

private:
  const uint8_t shamanbuff = 1;
};

class RagnarosTheFirelord : public Minion
{
public:
  RagnarosTheFirelord()
      : Minion("Ragnaros the Firelord", 0, 3, "Normal Attack", EntityType::MINION){};
  void applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex) override;
  std::shared_ptr<GameEntity> createInstance() override
  {
    return std::make_shared<RagnarosTheFirelord>();
  }
};
class BloodmageThalnos : public Minion
{
public:
  BloodmageThalnos()
      : Minion("Bloodmage Thalnos", 1, 1, "Normal Attack", EntityType::MINION){};
  void applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex) override;
  std::shared_ptr<GameEntity> createInstance() override
  {
    return std::make_shared<BloodmageThalnos>();
  }
};
class Brawl : public Minion
{
public:
  Brawl()
      : Minion("Brawl", 0, 0, "Destroy a random minion of the opposite player", EntityType::BRAWL){};
  void applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex) override;
  std::shared_ptr<GameEntity> createInstance() override
  {
    return std::make_shared<Brawl>();
  }
};
class Techies : public Minion
{
public:
  Techies()
      : Minion("Techies", 2, 1, "On dead it deals 3 damage to both hero", EntityType::TECHIES){};
  void applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex) override;
  std::shared_ptr<GameEntity> createInstance() override
  {
    return std::make_shared<Techies>();
  }
};
#endif // MINION_H
