#ifndef MOCK_H
#define MOCK_H
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameUi/GameUi.h"
#include "Helper/Helper.h"
#include "CardManager/CardFactory/Card.h"
#include "CardManager/Hero.h"
#include "MySocket/MySocket.h"
#include "GameEngine/GameEngine.h"
#define _ (testing::_)

#include "CardManager/CardManager.h"

// Mock class for MockCardManager
class MockCardManager : public CardManager {
public:
    MOCK_METHOD(void, CardManager_initManager, ());
    MOCK_METHOD(void, CardManager_getCardFromPocket, (std::vector<std::shared_ptr<Card>> &playerHand));
    MOCK_METHOD(std::shared_ptr<Hero>, CardManager_assignHeroToPlayer, (unsigned int heroNum));
    MOCK_METHOD(void, CardManager_pushCardToTable, (std::vector<std::shared_ptr<Card>> &playerTable, Card::CardType type));
    MOCK_METHOD(std::shared_ptr<Card>, CardManager_drawRandomCard, ());
};

#include "CardManager/Hero.h"

// Mock class for MockHero
class MockHero : public Hero {
public:
    MOCK_METHOD(void, initHero, ());
    MOCK_METHOD(bool, IsAlive, ());
    MOCK_METHOD(void, attackDefenderHero, (GameData_t &defender));
    MOCK_METHOD(void, takeDamage, (unsigned int damage));
};

#include "GameEngine/GameEngine.h"

// Mock class for MockGameEngine
class MockGameEngine : public GameEngine {
public:
    MOCK_METHOD(void, play, ());
    MOCK_METHOD(void, GameEngine_generatePlayerHero, ());
    MOCK_METHOD(void, GameEngine_generatePlayerCards, ());
    MOCK_METHOD(void, GameEngine_generateEntitiesForEachMode, (MySocket &socket));
    MOCK_METHOD(void, GameEngine_activeCard, (player_t player, int entityIndex));
    MOCK_METHOD(void, GameEngine_onClientMode, (MySocket &socket));
    MOCK_METHOD(void, GameEngine_onServerMode, (MySocket &socket));
    MOCK_METHOD(void, GameEngine_onOfflineMode, ());
    MOCK_METHOD(void, GameEngine_checkPlayerTurnCount, (MySocket &socket));
    MOCK_METHOD(void, GameEngine_clearPlayerDataStats, ());
    MOCK_METHOD(void, GameEngine_handingPlayerTurn, (player_t player, int choice));
    MOCK_METHOD(void, GameEngine_addUiObserver, (GameUi *uiObs));
    MOCK_METHOD(void, GameEngine_notifyUiObserver, (player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData));
};

#include "MySocket/MySocket.h"

// Mock class for MockMySocket
class MockMySocket : public MySocket {
public:
    MOCK_METHOD(void, sendInitCardPool, (const Card::CardType *host, size_t hostSize, const Card::CardType *client, size_t clientSize));
    MOCK_METHOD(void, recvInitCardPool, (Card::CardType *&host, int &hostSize, Card::CardType *&client, int &clientSize));
    MOCK_METHOD(void, sendPlayerChoice, (int choice));
    MOCK_METHOD(int, receivePlayerChoice, ());
    MOCK_METHOD(void, initializeServer, ());
    MOCK_METHOD(void, initializeClient, ());
};

#include "GameUi/GameUi.h"

// Mock class for MockGameUi
class MockGameUi : public GameUi {
public:
    MOCK_METHOD(void, GameUi_updateGameState, (player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData));
    MOCK_METHOD(void, GameUi_displayEntireTable, (const std::vector<GameData_t> &tableData));
    MOCK_METHOD(void, GameUi_displayGameRules, ());
    MOCK_METHOD(void, GameUi_displayModesOption, (int &option));
    MOCK_METHOD(void, GameUi_displayHandCard, (int &choice, const std::string &name, const std::vector<std::shared_ptr<Card>> &handCard));
    MOCK_METHOD(void, GameUi_waitForNextTurn, ());
    MOCK_METHOD(void, GameUi_waitForConfirm, ());
    MOCK_METHOD(void, GameUi_prepareConsole, ());
    MOCK_METHOD(void, GameUi_displayResult, (const std::vector<GameData_t> &tableData));
    MOCK_METHOD(void, GameUi_displayCard, (std::vector<std::vector<std::string>> &hand));
    MOCK_METHOD(void, GameUi_replaceTextFromLeftSide, (card_template_t &text, char flag, std::string new_text));
    MOCK_METHOD(void, GameUi_replaceTextFromRightSide, (card_template_t &text, char flag, std::string new_text));
    MOCK_METHOD(void, GameUi_prepareForReplace, (card_template_t &text));
    MOCK_METHOD(void, GameUi_getCenterTemplateWithMessage, (const std::vector<GameData_t> &tableData));
    MOCK_METHOD(card_template_t, GameUi_getTemplateWithText, (const std::string &color, card_template_t out, std::string name, int attack, int health, std::string skill, std::string status));
};

#endif