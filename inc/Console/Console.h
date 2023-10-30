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
    void displayGameResult(std::vector<std::string> message);
    int displayMenu(const std::string &title, const std::vector<std::string> &menuOptions);
    void displayTableStats(const std::string &title, const std::vector<std::string> &tableEntities);
    void displayHandEntities(const GameStats_t &data);
    ~Console();
    void waitForEnter();

private:
};

#endif // CONSOLE_H