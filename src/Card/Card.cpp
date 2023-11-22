
#include <iostream>
#include <string>
#include <memory>
#include "Card/Card.h"
#include "Card/CardFactory.h"
#include "Player/Player.h"
MinionCard::MinionCard(CardType type)
    : Card(type) {}
void MinionCard::play(unsigned int playerId, Player &attacker,Player &defender)
{
    attacker.stats.push_back("Player [" + std::to_string(attacker.getId() + 1) + "] active " + this->getDesciption());
    std::string line = "Player [" + std::to_string(attacker.getId() + 1) + "] attack Player [" + std::to_string(defender.getId() + 1) + "] with " + std::to_string(attacker.getHero()->getAttack()) + " damage";
    attacker.stats.push_back(line);
    this->getBuff(attacker.shamanCout);
    unsigned int damage = this->getAttack();
    // defender.getHero()->takeDamage(damage);
    // attacker.getHero()->attackDefenderHero(defender);
    attacker.stats.push_back(this->getName() + " attack " + defender.getHero()->getName() + " with " + std::to_string(damage) + " damage");
    if (!defender.getBattle().empty())
        for (auto it = defender.getBattle().begin(); it != defender.getBattle().end();)
        {
            auto &card = *it;
            card->takeDamage(damage);
            if (card->getHP() <= 0)
            {
                if (card->getCardType() == CardType::TECHIES)
                {
                    attacker.stats.push_back(attacker.getHero()->getName() + " Get 3 damage on Techies elimination");
                    attacker.getHero()->takeDamage(3);
                    defender.stats.push_back(defender.getHero()->getName() + " Get 3 damage on Techies elimination");
                    defender.getHero()->takeDamage(3);
                }
                else
                {
                    defender.stats.push_back(defender.getHero()->getName() + " card has been eliminated: " + card->getName());
                }
                if (card->getCardType() == CardType::SHAMAN)
                {
                    defender.shamanCout--;
                }
                it = defender.getBattle().erase(it);
            }
            else
            {
                ++it;
                attacker.stats.push_back(this->getName() + " attack " + card->getName() + " with " + std::to_string(damage) + " damage");
            }
        }
    else
    {
        attacker.stats.push_back(defender.getHero()->getName() + " had no card on table");
    }
}

std::string MinionCard::getDesciption()
{
    return getName() + " HP[" + std::to_string(getHP()) + "] ATK[" + std::to_string(getAttack()) + "]";
}

BuffCard::BuffCard(CardType type)
    : Card(type)
{
}
std::string BuffCard::getDesciption()
{
    return getName() + " " + getSkill() + " ACTIVE";
}
void BuffCard::play(unsigned int playerId, Player &attacker,Player &defender)
{
    std::cout << this->getDesciption() << " at BuffCard" << std::endl;

    attacker.stats.push_back("Player [" + std::to_string(attacker.getId() + 1) + "] active " + this->getDesciption());
    std::string line = "Player [" + std::to_string(attacker.getId() + 1) + "] attack Player [" + std::to_string(defender.getId() + 1) + "] with " + std::to_string(attacker.getHero()->getAttack()) + " damage";
    attacker.stats.push_back(line);
    attacker.getHero()->attackDefenderHero(defender);

    for (auto &minion : attacker.getBattle())
    {
        if (minion->getCardType() != CardType::SHAMAN)
        {
            minion->getBuff(-attacker.shamanCout);
        }
    }
    attacker.shamanCout = 0;
    if (!attacker.getBattle().empty())
    {

        for (auto &minion : attacker.getBattle())
        {
            if (minion->getCardType() == CardType::SHAMAN)
            {
                attacker.shamanCout++;
                attacker.stats.push_back(attacker.getHero()->getName() + " total damage buffed: " + std::to_string(attacker.shamanCout));
            }
        }
        for (auto &minion : attacker.getBattle())
        {
            if (minion->getCardType() != CardType::SHAMAN)
            {
                minion->getBuff(attacker.shamanCout);
            }
        }
    }
    else
    {
        attacker.stats.push_back(attacker.getHero()->getName() + " had no card to buff on table");
    }
}

std::string SpellCard::getDesciption()
{
    return getName() + " " + getSkill();
}

SpellCard::SpellCard(CardType type)
    : Card(type) {}

void SpellCard::play(unsigned int playerId, Player &attacker,Player &defender)
{

    attacker.stats.push_back("Player [" + std::to_string(attacker.getId() + 1) + "] active " + this->getDesciption());
    std::string line = "Player [" + std::to_string(attacker.getId() + 1) + "] attack Player [" + std::to_string(defender.getId() + 1) + "] with " + std::to_string(attacker.getHero()->getAttack()) + " damage";
    attacker.stats.push_back(line);
    attacker.getHero()->attackDefenderHero(defender);
    if (!defender.getBattle().empty())
    {
        int randomIndex = rand() % defender.getBattle().size();
        auto &cardRemoved = defender.getBattle()[randomIndex];
        if (cardRemoved->getCardType() == CardType::TECHIES)
        {
            attacker.stats.push_back(attacker.getHero()->getName() + "Get 3 damage on Techies elimination");
            attacker.getHero()->takeDamage(3);
            defender.stats.push_back(defender.getHero()->getName() + "Get 3 damage on Techies elimination");
            defender.getHero()->takeDamage(3);
        }
        defender.stats.push_back("Card " + cardRemoved->getDesciption() + " have been removed from table by Brawl");
        defender.getBattle().erase(defender.getBattle().begin() + randomIndex);
    }
    else
    {
        defender.stats.push_back(attacker.getHero()->getName() + " had no card on table");
    }
}