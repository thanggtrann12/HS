#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <iostream>
#include <string>
#include <memory>
#include "Card/Card.h"
class Player;
class MinionCard : public Card
{
public:
    MinionCard(CardType type);
    void play(unsigned int playerId, std::vector<Player> &players) override;
    std::string getDesciption() override;
};

class BuffCard : public Card
{
public:
    BuffCard(CardType type);
    void play(unsigned int playerId, std::vector<Player> &players) override;
    std::string getDesciption() override;
};

class SpellCard : public Card
{
public:
    SpellCard(CardType type);
    void play(unsigned int playerId, std::vector<Player> &players) override;
    std::string getDesciption() override;
};

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