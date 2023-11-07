
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
    attacker.hero->Hero_attackDefenderHero(defender);
    unsigned int damage = attacker.handEntities[cardPlayed]->getAttack();
    if (!defender.tableEntities.empty())
        for (auto &card : defender.tableEntities)
        {
            card->takeDamage(damage);
            if (card->getHP() <= 0 && card->getCardType() == Card::CardType::TECHIES)
            {
                attacker.stats.push_back(attacker.hero->Hero_getName() + "Get 3 damage on Techies elimination");
                attacker.hero->Hero_getDamage(3);
                defender.stats.push_back(defender.hero->Hero_getName() + "Get 3 damage on Techies elimination");
                defender.hero->Hero_getDamage(3);
            }
            else if (card->getHP() <= 0)
            {
                defender.stats.push_back(defender.hero->Hero_getName() + "card have been elimination: " + card->getName());
            }
        }
    else
    {
        attacker.stats.push_back(defender.hero->Hero_getName() + "had no card on table");
    }
}
BuffCard::BuffCard(const std::string &name, int hp, int attack, const std::string &skill, Card::CardType type)
    : Card(name, hp, attack, skill, type) {}

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
        attacker.stats.push_back(attacker.hero->Hero_getName() + "had no card on table");
    }
}
SpellCard::SpellCard(const std::string &name, Card::CardType type)
    : Card(name, 0, 0, "No Skill", type) {}

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
            attacker.stats.push_back(attacker.hero->Hero_getName() + "Get 3 damage on Techies elimination");
            attacker.hero->Hero_getDamage(3);
            defender.stats.push_back(defender.hero->Hero_getName() + "Get 3 damage on Techies elimination");
            defender.hero->Hero_getDamage(3);
        }
        defender.tableEntities.erase(defender.tableEntities.begin() + randomIndex);
    }
    else
    {
        attacker.stats.push_back(attacker.hero->Hero_getName() + "had no card on table");
    }
}