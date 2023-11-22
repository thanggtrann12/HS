#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Player/Player.h"

// Mock class for Mock_Player

class MockPlayer : public Player
{
public:
    MockPlayer(PlayerId playerId, Ui *ui) : Player(playerId, ui) {}

    MOCK_METHOD(void, drawCard, (unsigned int), ());
    MOCK_METHOD(void, updateCard, (CardType), ());
    MOCK_METHOD(unsigned int, pickACardToPlay, ());
    MOCK_METHOD(void, activeCardOnHand, (Player &, Player &, std::vector<std::shared_ptr<Card>>::iterator), ());
    MOCK_METHOD(void, setHero, (HeroType), ());
    MOCK_METHOD(std::string, getBasicInfo, (), ());
    MOCK_METHOD(std::shared_ptr<Hero> &, getHero, (), ());
    MOCK_METHOD(void, attackOpponent, (Player &), ());
};

#endif // MOCK_PLAYER_H
