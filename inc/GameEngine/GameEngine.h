#ifndef GAME_H
#define GAME_H
#include "MySocket/MySocket.h"
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
    void generatePlayerHero();
    void generatePlayerCards();
    void generateEntitiesForEachMode(MySocket &socket);
    void activeCard(player_t player, int entityIndex);
    void onClientMode(MySocket &socket);
    void onServerMode(MySocket &socket);
    void onOfflineMode();
    void checkPlayerTurnCount(MySocket &socket);
    void clearPlayerDataStats();
    void handingPlayerTurn(player_t player, int choice);

protected:
    GameUi gameUi;
    std::vector<GameUi *> observers;
    CardManager manager;
    std::vector<GameData_t> GameData;
    GameData_t ServerData;
    GameData_t ClientData;
    int option;
    void addUiObserver(GameUi *uiObs);
    void notifyUiObserver(player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData);
};

#endif // GAME_H
