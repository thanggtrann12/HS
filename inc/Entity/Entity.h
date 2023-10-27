#ifndef UNITS_H
#define UNITS_H
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
typedef struct
{
  std::shared_ptr<Hero> hero;
  std::vector<std::shared_ptr<GameEntity>> tableEntities;
  std::vector<std::shared_ptr<GameEntity>> handEntities;
  std::vector<std::string> stats;
  int turnCount = 0;
} GameData_t;
class GameEntity
{
public:
  GameEntity() : name("DefaultName"), attack(0), health(0), skill("DefaultSkill"), type(EntityType::HERO) {}
  GameEntity(std::string n, int a, int h, std::string sk, EntityType tp);
  virtual void applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex) {}

  virtual std::shared_ptr<GameEntity> createInstance()
  {
    return std::make_shared<GameEntity>();
  }
  std::string GetName() const;
  int GetAttack() const;
  int GetHealth() const;
  bool IsAlive();
  EntityType GetEntitiesType() const;
  void TakeDamage(int damage);
  void AttackHero(std::shared_ptr<Hero> &hero, int damage);
  std::string GetDescription() const;
  void SetAttack(int _newAtk);
  bool IsApply();
  void Applied();
  ~GameEntity();

protected:
  std::string name;
  std::string skill;
  EntityType type;
  bool isUsed = false;
  int attack;
  int health;
  int maxhealth;
};
class Hero : public GameEntity
{
public:
  Hero() : GameEntity() {}
  Hero(std::string n, int a, int h, const std::string &sk, EntityType tp) : GameEntity(n, a, h, sk, tp) {}
  void InitHeroes();
  std::vector<std::shared_ptr<Hero>> &GetHeroes();

private:
  std::vector<std::shared_ptr<Hero>> heroes;
};

#endif // UNITS_H
