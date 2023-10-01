#ifndef CONSOLE_H
#define CONSOLE_H

#include "Game/Game.h"
class Console
{
public:
    Console();

    void displayWelcomeMessage(int &choice, std::string &host);
    void displayGameState(std::vector<std::string> currentPlayer, std::vector<std::string> opponentPlayer, std::vector<std::string> message);
    void displayGameResult(std::vector<std::string> message);
    ~Console();

private:
};

#endif // CONSOLE_H