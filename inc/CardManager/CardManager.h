#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include <vector>
#include <iostream>
#include <memory>
#include "Card/Card.h"
class Player;
class CardManager
{
public:
    CardManager();
    std::shared_ptr<Card> getCardFromPocket();
    void generateCardFromCardType(std::vector<std::shared_ptr<Card>> &playerTable, CardType type);
    void activeCard(Player &attacker,Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed);
    void removeFromHand(std::vector<std::shared_ptr<Card>> &playerHand, std::vector<std::shared_ptr<Card>>::iterator cardRemove);
    ~CardManager(){};

private:
    std::vector<std::shared_ptr<Card>> cardPocket;
};

#endif // CARD_MANAGER_H