
#ifndef MOCK_CARD_H
#define MOCK_CARD_H

 #include "gtest/gtest.h"
 #include "gmock/gmock.h"
#include "Card/Card.h"

// Mock class for Mock_Card
// Mock class for Card
class Mock_Card : public Card {
public:
    MOCK_METHOD(void, play, (unsigned int playerId, std::vector<Player> &players), (override));
};

#endif // MOCK_CARD_H
