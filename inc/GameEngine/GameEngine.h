#ifndef GAME_H
#define GAME_H
#include "MySocket/Socket.h"
#include <ctime>
#include <cstdlib>
#include "Helper/Helper.h"
#include "CardManager/CardManager.h"
#include "GameUi/GameUi.h"
#include <iostream>
const int SERVER_MODE = 1;
const int CLIENT_MODE = 2;
const int SHOW_GAME_RULES = 4;
class Console;

class GameEngine
{
public:
    GameEngine();
    void play();
    ~GameEngine(){};

private:
    void GameEngine_generatePlayerHero();
    void GameEngine_generatePlayerCards();
    void GameEngine_generateEntitiesForEachMode(MySocket &socket);
    void GameEngine_distributeCardToPlayerHand();
    void GameEngine_deleteCardFromBattleYard(player_t player, int entityIndex);
    void GameEngine_activeCard(player_t player, int entityIndex);
    void GameEngine_onClientMode(MySocket &socket);
    void GameEngine_onServerMode(MySocket &socket);
    void GameEngine_onOfflineMode();
    void GameEngine_checkPlayerTurnCount(MySocket &socket);
    void clearPlayerDataStats();
    void GameEngine_handingPlayerTurn(player_t player, int choice);

protected:
    GameUi gameUi;
    std::vector<GameUi *> observers;
    CardManager manager;
    std::vector<GameData_t> GameData;
    GameData_t ServerData;
    GameData_t ClientData;
    int option;
    void GameEngine_addUiObserver(GameUi *uiObs);
    void GameEngine_notifyUiObserver(player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData);
};

#endif // GAME_H
