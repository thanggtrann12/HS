#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <memory>
#include "assets/CardData.h"
#include <vector>
class Player;
class Card
{
public:
    virtual ~Card() = default;
    virtual void play(unsigned int playerId, Player &attacker,Player &defender) = 0;
    const std::string &getName() const { return card.name; }
    int getHP() const { return card.health; }
    int getAttack() const { return card.attack; }
    void takeDamage(unsigned int damage) { card.health = (card.health > damage) ? card.health - damage : 0; }
    CardType getCardType() const { return card.type; }
    void getBuff(int damage) { card.attack += damage; }
    const std::string &getSkill() const { return card.skill; }
    virtual std::string getDesciption() = 0;

protected:
    Card(CardType type) : card(cardsData[type]) {}

private:
    CardData card;
};

#endif // CARD_H