#ifndef CONSOLE_H
#define CONSOLE_H

#include "Game/Game.h"
class Console
{
public:
    Console();
    void clearConsole();
    void loadingConsole();
    void displayWelcomeMessage(int &choice);
    void displayGameState(std::vector<std::string> currentPlayer, std::vector<std::string> opponentPlayer, std::vector<std::string> message);
    void displayGameResult(std::vector<std::string> message);
    int displayMenu(const std::string &title, const std::vector<std::string> &menuOptions);
    void displayTableEntitiesMenu(const std::string &title, const std::vector<std::string> &tableEntities);
    ~Console();
    void waitForEnter();

private:
};

#endif // CONSOLE_H