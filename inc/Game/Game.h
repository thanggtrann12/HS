#ifndef GAME_H
#define GAME_H

#include "Units/Hero.h"
#include "Units/Minion.h"
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
  std::vector<std::shared_ptr<Hero>> heroes;
  std::vector<std::shared_ptr<Minion>> cards;
  std::vector<std::string> message;
  std::vector<int> turnCounts;
  void initializeHeroes();
  void initializeCards();
  void dealInitialCards();
  std::shared_ptr<Minion> drawRandomCard();
  int mode = 0;
  std::string host;
  void drawCard(int playerIndex);
  void playCard(int currentPlayerIndex, int opponentIndex);
  bool resolveBrawl(int opponentIndex);
  void displayGameState(int currentPlayerIndex, int opponentIndex);
  void displayGameResult(int winnerIndex);
  void displayBattlefield(int currentPlayerIndex);
  bool isTurnCountReached(int playerIndex);
  void resetTurnCount(int playerIndex);
  Console *console;
};

#endif // GAME_H
