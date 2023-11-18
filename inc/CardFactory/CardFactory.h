#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <iostream>
#include <string>
#include <memory>
#include "CardFactory/Card.h"

class CardFactory
{
public:
    virtual std::shared_ptr<Card> createCard(CardType type) = 0;
};

class MinionCardFactory : public CardFactory
{
public:
    std::shared_ptr<Card> createCard(CardType type) override
    {
        return std::make_shared<MinionCard>(type);
    }
};

class BuffCardFactory : public CardFactory
{
public:
    std::shared_ptr<Card> createCard(CardType type) override
    {
        return std::make_shared<BuffCard>(type);
    }
};

class SpellCardFactory : public CardFactory
{
public:
    std::shared_ptr<Card> createCard(CardType type) override
    {
        return std::make_shared<SpellCard>(type);
    }
};
#endif // CARD_FACTORY_H