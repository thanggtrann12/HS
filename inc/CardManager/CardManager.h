#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include <vector>
#include <iostream>
#include <memory>
#include "Card/Card.h"
class CardManager
{
public:
    CardManager();
    std::shared_ptr<Card> getCardFromPocket();
    void generateCardFromCardType(std::vector<std::shared_ptr<Card>> &playerTable, CardType type);
    virtual void activeCard(Player &attacker, Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed);
    ~CardManager(){};

private:
    std::vector<std::shared_ptr<Card>> cardPocket;
};

#endif // CARD_MANAGER_H