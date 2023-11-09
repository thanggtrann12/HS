
#include <iostream>
#include <string>
#include <memory>
#include "CardManager/CardFactory/Card.h"
#include "CardManager/Hero.h"
#include "Helper/Helper.h"
MinionCard::MinionCard(const std::string &name, int hp, int attack, Card::CardType type)
    : Card(name, hp, attack, "No Skill", type) {}
void MinionCard::play(unsigned int playerIndex, unsigned int cardPlayed, std::vector<GameData_t> &gameData)
{
  auto &attacker = gameData[playerIndex];
  auto &defender = gameData[1 - playerIndex];
  unsigned int damage = attacker.handEntities[cardPlayed]->getAttack();
  defender.hero->takeDamage(damage);
  attacker.stats.push_back(attacker.handEntities[cardPlayed]->getName() + " attack " + defender.hero->getName() + "with " + std::to_string(damage) + " damage");
  if (!defender.tableEntities.empty())
    for (auto it = defender.tableEntities.begin(); it != defender.tableEntities.end();)
    {
      auto &card = *it;
      card->takeDamage(damage);
      if (card->getHP() <= 0)
      {
        if (card->getCardType() == Card::CardType::TECHIES)
        {
          attacker.stats.push_back(attacker.hero->getName() + " Get 3 damage on Techies elimination");
          attacker.hero->takeDamage(3);
          defender.stats.push_back(defender.hero->getName() + " Get 3 damage on Techies elimination");
          defender.hero->takeDamage(3);
        }
        else
        {
          defender.stats.push_back(defender.hero->getName() + " card has been eliminated: " + card->getName());
        }

        it = defender.tableEntities.erase(it);
      }
      else
      {
        ++it;
        attacker.stats.push_back(attacker.handEntities[cardPlayed]->getName() + " attack " + card->getName() + "with " + std::to_string(damage) + " damage");
      }
    }
  else
  {
    attacker.stats.push_back(defender.hero->getName() + " had no card on table");
  }
}

std::string MinionCard::getDesciption()
{
  return getName() + " HP[" + std::to_string(getHP()) + "] ATK[" + std::to_string(getAttack()) + "]";
}

BuffCard::BuffCard(const std::string &name, int hp, int attack, const std::string &skill, Card::CardType type)
    : Card(name, hp, attack, skill, type)
{
}
std::string BuffCard::getDesciption()
{
  return getName() + " " + getSkill() + " " + (isUsed() ? "ACTIVE" : "INACTIVE");
}
void BuffCard::play(unsigned int playerIndex, unsigned int cardPlayed, std::vector<GameData_t> &gameData)
{
  auto &attacker = gameData[playerIndex];
  auto &defender = gameData[1 - playerIndex];
  if (!attacker.tableEntities.empty())
  {

    for (auto &minion : attacker.tableEntities)
    {
      if (minion->getCardType() != Card::CardType::SHAMAN && !minion->isUsed())
      {
        attacker.stats.push_back("Card buffed: ");
        minion->getBuff(1);
        attacker.stats.push_back("  -" + minion->getName() + std::to_string(minion->getAttack()));
        minion->setUsed();
      }
    }
  }
  else
  {
    attacker.stats.push_back(attacker.hero->getName() + " had no card to buff on table");
  }
}

std::string SpellCard::getDesciption()
{
  return getName() + " " + getSkill();
}

SpellCard::SpellCard(const std::string &name, const std::string &skill, Card::CardType type)
    : Card(name, 0, 0, skill, type) {}

void SpellCard::play(unsigned int playerIndex, unsigned int cardPlayed, std::vector<GameData_t> &gameData)
{
  auto &attacker = gameData[playerIndex];
  auto &defender = gameData[1 - playerIndex];
  if (!defender.tableEntities.empty())
  {
    int randomIndex = rand() % defender.tableEntities.size();
    auto &cardRemoved = defender.tableEntities[randomIndex];
    if (cardRemoved->getCardType() == Card::CardType::TECHIES)
    {
      attacker.stats.push_back(attacker.hero->getName() + "Get 3 damage on Techies elimination");
      attacker.hero->takeDamage(3);
      defender.stats.push_back(defender.hero->getName() + "Get 3 damage on Techies elimination");
      defender.hero->takeDamage(3);
    }
    defender.tableEntities.erase(defender.tableEntities.begin() + randomIndex);
  }
  else
  {
    defender.stats.push_back(attacker.hero->getName() + " had no card on table");
  }
  for (auto it = attacker.tableEntities.begin(); it != attacker.tableEntities.end();)
  {
    auto &card = *it;
    if (card->getCardType() == Card::CardType::BRAWL)
    {
      it = attacker.tableEntities.erase(it);
    }
    else
    {
      ++it;
    }
  }
}