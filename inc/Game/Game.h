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
  void removeEntitiesOnTable(uint8_t playerIndex, uint8_t entities);
  void removeEntitiesOnHand(uint8_t playerIndex, uint8_t entities);
  void addBattleEntities(uint8_t playerIndex, uint8_t entities);
  void activateEntitiesAndHeroAttack(uint8_t playerIndex, uint8_t entityIndex);

protected:
  Console *console;
  Hero playerHero;
  std::vector<std::shared_ptr<GameEntity>> cardsPool;
  std::vector<GameData_t> playerData;
  int CLIENT_INDEX = 0;
  int SERVER_INDEX = 1;
};

#endif // GAME_H
