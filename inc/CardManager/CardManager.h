#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include "CardManager/CardFactory/Card.h"
#include "CardManager/Hero.h"
class CardManager
{
public:
    CardManager();
    void CardManager_initManager();
    void CardManager_getCardFromPocket(std::vector<std::shared_ptr<Card>> &playerHand);
    std::shared_ptr<Hero> CardManager_assignHeroToPlayer(unsigned int heroNum);
    void CardManager_pushCardToTable(std::vector<std::shared_ptr<Card>> &playerTable, Card::CardType type);
    std::shared_ptr<Card> CardManager_drawRandomCard();
    ~CardManager(){};

private:
    Hero hero;
    std::vector<std::shared_ptr<Card>> cardPocket;
};

#endif // CARD_MANAGER_H