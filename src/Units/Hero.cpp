#include "Units/Hero.h"
#include <iostream>
#include <algorithm>

Hero::Hero(const std::string &name, int maxHP, int attack)
    : Units(name, maxHP, attack, CardType::HERO) {}

void Hero::addCard(std::shared_ptr<Minion> card)
{
    hand.push_back(card);
}
void Hero::removeBattleCard(std::shared_ptr<Minion> card)
{
    auto it = std::find(battleCards.begin(), battleCards.end(), card);

    if (it != battleCards.end())
    {
        std::cout << "Remove " << card->getDescription() << std::endl;
        battleCards.erase(it);
    }
    else
    {
        std::cerr << "Card not found in battleCards." << std::endl;
    }
}

void Hero::addToBattle(std::shared_ptr<Minion> card)
{
    battleCards.push_back(card);
}

std::shared_ptr<Minion> Hero::playCard(int index)
{
    if (index >= 0 && index < hand.size())
    {
        auto playedCard = hand[index];
        addToBattle(hand[index]);
        hand.erase(hand.begin() + index);
        return playedCard;
    }
    return nullptr;
}

int Hero::getNumCards() const
{
    return hand.size();
}

std::vector<std::shared_ptr<Minion>> &Hero::getHandCards()
{
    return hand;
}

std::vector<std::shared_ptr<Minion>> &Hero::getBattleCard()
{
    return battleCards;
}
