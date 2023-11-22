#ifndef MOCK_CARDMANAGER_H
#define MOCK_CARDMANAGER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "CardManager/CardManager.h"

// Mock class for Mock_CardManager
class Mock_CardManager : public CardManager {
public:
    MOCK_METHOD(std::shared_ptr<Card>, getCardFromPocket, ());
    MOCK_METHOD(void, generateCardFromCardType, (std::vector<std::shared_ptr<Card>> &playerTable, CardType type));
    MOCK_METHOD(void, activeCard, (Player &attacker, Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed));
    MOCK_METHOD(void, removeFromHand, (std::vector<std::shared_ptr<Card>> &playerHand, std::vector<std::shared_ptr<Card>>::iterator cardRemove));
};
#endif // MOCK_CARDMANAGER_H
