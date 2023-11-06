#ifndef GAME_H
#define GAME_H

#include "GameEntities/Minion.h"
#include "GameEntities/Hero.h"
#include "GameEntities/Entity.h"
#include "MySocket/Socket.h"
#include <ctime>
#include <cstdlib>

#include <iostream>
#include "GameUi/GameUi.h"
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
    void GameEngine_generateHeroPocket();
    void GameEngine_generateCardPocket();
    void GameEngine_generateEntitiesForEachMode(MySocket &socket);
    void GameEngine_distributeCardToPlayerHand();
    void GameEngine_deleteCardFromBattleYard(int playerIndex, int entityIndex);
    void GameEngine_placeCardToBattleYard(int playerIndex, int entityIndex);
    void GameEngine_activeCardOnBattleYard(int playerIndex);
    void GameEngine_onClientMode(MySocket &socket);
    void GameEngine_onServerMode(MySocket &socket);
    void GameEngine_onOfflineMode();
    void GameEngine_checkPlayerTurnCount(MySocket &socket);
    void clearPlayerDataStats();
    void GameEngine_handingPlayerTurn(int playerIndex, int choice);
protected:
    GameUi gameUi;
    std::vector<GameUi*> observers;
    Hero playerHero;
    std::vector<std::shared_ptr<Minion>> cardsPool;
    std::vector<GameData_t> GameData;
    GameData_t ServerData;
    GameData_t ClientData;
    int option;
    int CLIENT_INDEX = 0;
    int SERVER_INDEX = 1;
    void GameEngine_addUiObserver(GameUi *uiObs);
    void GameEngine_notifyUiObserver(int playerIndex, int state, int &cardChoiced, const std::vector<GameData_t> &tableData);
};

#endif // GAME_H
