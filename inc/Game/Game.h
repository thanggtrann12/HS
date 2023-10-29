#ifndef GAME_H
#define GAME_H

#include "Entity/Minion.h"
#include "Entity/Entity.h"
#include "MySocket/Socket.h"
#include <ctime>
#include <cstdlib>
#include <Console/Console.h>
#include <iostream>

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
    void activateEntity(int playerIndex);

protected:
    Console *console;
    Hero playerHero;
    std::vector<std::shared_ptr<Minion>> cardsPool;
    std::vector<GameData_t> playerData;
    int CLIENT_INDEX = 0;
    int SERVER_INDEX = 1;
};

#endif // GAME_H
