#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include "CardManager/CardFactory/Card.h"
#include "CardManager/GameEntities/Hero.h"
class CardManager
{
public:
    CardManager(){};
    void CardManager_initCardManager();
    std::vector<std::shared_ptr<Card>> &CardManager_getCardFromPocket();
    ~CardManager(){};

private:
    std::vector<std::shared_ptr<Card>> cardPocket;
};

#endif // CARD_MANAGER_H