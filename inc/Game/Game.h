#ifndef GAME_H
#define GAME_H

#include "Entity/Minion.h"
#include "Entity/Hero.h"
#include "Entity/Entity.h"
#include "MySocket/Socket.h"
#include <ctime>
#include <cstdlib>
#include <Console/Console.h>
#include <iostream>
const int SERVER_MODE = 1;
const int CLIENT_MODE = 2;
class Console;

class Game
{
public:
    Game();
    void play();

private:
    void initializeHeroes();
    void initializeCards();
    void dealInitialCards();
    void removeEntityFromTable(int playerIndex, int entityIndex);
    void removeEntityFromHand(int playerIndex, int entityIndex);
    void addEntityToTable(int playerIndex, int entityIndex);
    void showEntitiesOnTable(const GameStats_t &currentPlayer, const GameStats_t &opponentPlayer);
    void activateEntity(int playerIndex);
    void showTableStats(int playerIndex);
    void playClientMode(MySocket &socket);
    void playServerMode(MySocket &socket);
    void playOfflineMode();
    void clearPlayerDataStats();
    GameStats_t getGameStatsForPlayer(int playerIndex);
    std::string formatBasicHeroStats(const std::string &heroName, int health, int turnCount);

protected:
    Console *console;
    Hero playerHero;
    std::vector<std::string> tableEntitiesPlayer1;
    std::vector<std::string> tableEntitiesPlayer2;
    std::vector<std::shared_ptr<Minion>> cardsPool;
    std::vector<GameData_t> playerData;
    int mode;
    int CLIENT_INDEX = 0;
    int SERVER_INDEX = 1;
};

#endif // GAME_H
