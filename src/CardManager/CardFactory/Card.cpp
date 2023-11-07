
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
    attacker.hero->attackDefenderHero(defender);
    unsigned int damage = attacker.handEntities[cardPlayed]->getAttack();
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
                    attacker.hero->getDamage(3);
                    defender.stats.push_back(defender.hero->getName() + " Get 3 damage on Techies elimination");
                    defender.hero->getDamage(3);
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
    attacker.handEntities[cardPlayed];
    if (!attacker.tableEntities.empty())
    {
        attacker.stats.push_back("Card buffed: ");
        for (auto &minion : attacker.tableEntities)
        {
            if (minion->getCardType() != Card::CardType::SHAMAN && !minion->isUsed())
            {
                minion->getBuff(1);
                attacker.stats.push_back("  -" + minion->getName() + std::to_string(minion->getAttack()));
                minion->setUsed();
            }
        }
    }
    else
    {
        attacker.stats.push_back(attacker.hero->getName() + " had no card on table");
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
    if (!attacker.tableEntities.empty())
    {
        int randomIndex = rand() % defender.tableEntities.size();
        auto &cardRemoved = defender.tableEntities[randomIndex];
        if (cardRemoved->getCardType() == Card::CardType::TECHIES)
        {
            attacker.stats.push_back(attacker.hero->getName() + "Get 3 damage on Techies elimination");
            attacker.hero->getDamage(3);
            defender.stats.push_back(defender.hero->getName() + "Get 3 damage on Techies elimination");
            defender.hero->getDamage(3);
        }
        defender.tableEntities.erase(defender.tableEntities.begin() + randomIndex);
    }
    else
    {
        attacker.stats.push_back(attacker.hero->getName() + "had no card on table");
    }
}