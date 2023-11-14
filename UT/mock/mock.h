#ifndef MOCK_H
#define MOCK_H
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameUi/GameUi.h"
#include "Helper/Helper.h"
#include "CardManager/CardFactory/Card.h"
#include "CardManager/Hero.h"
class MockGameUi : public GameUi
{
public:
#define _ (testing::_)
    MOCK_METHOD(void, GameUi_updateGameState, (player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData));
    MOCK_METHOD(void, GameUi_waitForConfirm, ());
    MOCK_METHOD(void, GameUi_waitForNextTurn, ());
    MOCK_METHOD(void, GameUi_prepareConsole, ());
    MOCK_METHOD(void, GameUi_displayEntireTable, (const std::vector<GameData_t> &tableData));
    MOCK_METHOD(void, GameUi_displayCard, (std::vector<std::vector<std::string>> & hand));
    MOCK_METHOD(void, GameUi_replaceTextFromLeftSide, (card_template_t & text, char flag, std::string new_text));
    MOCK_METHOD(void, GameUi_replaceTextFromRightSide, (card_template_t & text, char flag, std::string new_text));
    MOCK_METHOD(void, GameUi_prepareForReplace, (card_template_t & text));
    MOCK_METHOD(card_template_t, GameUi_getTemplateWithText, (const std::string &color, card_template_t out, std::string name, int attack, int health, std::string skill, std::string status));
    MOCK_METHOD(void, GameUi_getCenterTemplateWithMessage, (const std::vector<GameData_t> &tableData));
    MOCK_METHOD(void, GameUi_displayGameRules, ());
    MOCK_METHOD(void, GameUi_displayModesOption, (int &option));
    MOCK_METHOD(void, GameUi_displayHandCard, (int &choice, const std::string &name, const std::vector<std::shared_ptr<Card>> &handCard));
    MOCK_METHOD(void, GameUi_displayResult, (const std::vector<GameData_t> &tableData));
};
#endif