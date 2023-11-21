#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Player/Player.h"

// Mock class for Mock_Player
class Mock_Player : public Player {
public:
    MOCK_METHOD(void, drawCard, (unsigned int num));
    MOCK_METHOD(void, updateCard, (CardType type));
    MOCK_METHOD(PlayerId, getId, ());
    MOCK_METHOD(unsigned int, pickACardToPlay, ());
    MOCK_METHOD(void, addCardToBattle, (std::vector<std::shared_ptr<Card>>::iterator cardPlayed));
    MOCK_METHOD(void, setHero, (HeroType type));
    MOCK_METHOD(std::string, getBasicInfo, ());
    MOCK_METHOD(void, setId, (PlayerId id));
    MOCK_METHOD(std::vector<std::shared_ptr<Card>>, getHand, ());
    MOCK_METHOD(std::vector<std::shared_ptr<Card>>, getBattle, ());
};

#endif // MOCK_PLAYER_H
