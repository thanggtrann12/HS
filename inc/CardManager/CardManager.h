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
    void CardManager_assignHeroToPlayer(std::shared_ptr<Hero> &playerHero);
    std::shared_ptr<Card> CardManager_drawRandomCard();
    ~CardManager(){};

private:
    Hero hero;
    std::vector<std::shared_ptr<Card>> cardPocket;
};

#endif // CARD_MANAGER_H