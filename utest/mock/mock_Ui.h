#ifndef MOCK_UI_H
#define MOCK_UI_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "UI/Ui.h"

// Mock class for Mock_Ui
class Mock_Ui : public Ui {
public:
    MOCK_METHOD(void, displayMenuScreen, (unsigned int &choicedMode));
    MOCK_METHOD(void, selectCard, (Player &player, unsigned int &choicedCard));
    MOCK_METHOD(void, displayPlayerCard, (Player &player, unsigned int &choicedCard));
    MOCK_METHOD(void, displayCardList, (std::vector<std::shared_ptr<Card>> &playerHandCard, int currentIndex));
    MOCK_METHOD(void, displayBattle, (std::vector<Player> &players, unsigned int playerId));
    MOCK_METHOD(void, displayResult, (Player &player));
    MOCK_METHOD(void, onUiStateChangeOnState, (UiState state, std::vector<Player> &players, unsigned int playerId, unsigned int &clone));
};
#endif // MOCK_UI_H
