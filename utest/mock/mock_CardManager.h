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
};
#endif // MOCK_CARDMANAGER_H
