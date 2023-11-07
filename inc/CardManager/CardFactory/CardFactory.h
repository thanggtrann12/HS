#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <iostream>
#include <string>
#include <memory>
#include "CardManager/CardFactory/Card.h"

class CardFactory
{
public:
    virtual std::shared_ptr<Card> createCard(Card::CardType type) = 0;
};

class MinionCardFactory : public CardFactory
{
public:
    std::shared_ptr<Card> createCard(Card::CardType type) override
    {
        switch (type)
        {
        case Card::CardType::FIRELORD:
            return std::make_shared<MinionCard>("Ragnaros the Firelord", 1, 3, type);
        case Card::CardType::THALNOS:
            return std::make_shared<MinionCard>("Bloodmage Thalnos", 1, 1, type);
        case Card::CardType::TECHIES:
            return std::make_shared<MinionCard>("Techies", 2, 1, type);
        default:
            return nullptr;
        }
    }
};

class BuffCardFactory : public CardFactory
{
public:
    std::shared_ptr<Card> createCard(Card::CardType type) override
    {
        return std::make_shared<BuffCard>("Flametongue Totem", 1, 1, "Provides all alliance minions with a +1 Attack bonus", type);
    }
};

class SpellCardFactory : public CardFactory
{
public:
    std::shared_ptr<Card> createCard(Card::CardType type) override
    {
        return std::make_shared<SpellCard>("Destroy a random minion of the opposite playe", type);
    }
};
#endif // CARD_FACTORY_H