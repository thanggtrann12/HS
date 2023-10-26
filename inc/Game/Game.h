#ifndef GAME_H
#define GAME_H

#include "Units/Hero.h"
#include "Units/Minion.h"
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
  void displayHand(int playerIndex) const;
  void drawCard(int playerIndex);
  void playCard(int currentPlayerIndex, int opponentIndex, int cardChoice);
  bool resolveBrawl(int opponentIndex);
  void getGameStats(data_t &data);
  void displayGameResult(int winnerIndex);
  void displayBattlefield(int currentPlayerIndex);
  bool calculatePlayerTurnCount();
  Console *console;
  int clientIndex = 0, serverIndex = 1;
};

#endif // GAME_H
