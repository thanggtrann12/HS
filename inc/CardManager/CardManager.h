#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include "CardFactory/Card.h"
#include "CardManager/Hero.h"
class CardManager
{
public:
    CardManager();
    void initManager();
    void getCardFromPocket(std::vector<std::shared_ptr<Card>> &playerHand);
    std::shared_ptr<Hero> assignHeroToPlayer(unsigned int heroNum);
    void pushCardToTable(std::vector<std::shared_ptr<Card>> &playerTable, CardType type);
    std::shared_ptr<Card> drawRandomCard();
    ~CardManager(){};

private:
    Hero hero;
    std::vector<std::shared_ptr<Card>> cardPocket;
};

#endif // CARD_MANAGER_H