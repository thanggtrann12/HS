// Console.cpp
#include "Console/Console.h"
#include "Game/Game.h"
#include <iostream>
#include <iomanip>
Console::Console()
{
    std::cout << "init display" << std::endl;
}
void Console::displayWelcomeMessage(int &choice, std::string &host)
{
    std::string hostName;
    int option = 0;
    std::cout << "=====================================================================" << std::endl;

    std::cout << "#" << std::setw(68) << "#" << std::endl;
    std::cout << "#" << std::setw(68) << "#" << std::endl;
    std::cout << "#                    *| WELCOME TO MY DAMN GAME |*                  #" << std::endl;
    std::cout << "#                        Choose option to play                      #" << std::endl;
    std::cout << "#                        1. Host a game                             #" << std::endl;
    std::cout << "#                        2. Join a game                             #" << std::endl;
    std::cout << "#                     Please Enter your choose                      #" << std::endl;

    std::cout << "#" << std::setw(68) << "#" << std::endl;
    std::cout << "#" << std::setw(68) << "#" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cin >> choice;
    if (choice == 1)
    {
        std::cout << std::setw(29) << " "
                  << "Enter your host name:   ";
        std::cin >> hostName;
        std::cout << std::endl;
        host = hostName;
    }
    choice = option;
}

void Console::displayGameState(std::vector<std::string> currentPlayer, std::vector<std::string> opponentPlayer, std::vector<std::string> message)
{
    const int colWidth = 10;
    for (int i = 0; i < message.size(); i++)
    {
        std::cout << message[i] << std::endl;
    }
    std::cout << "=====================================================================" << std::endl;
    std::cout << "# Player    Hero HP   Hero Attack     Total Damage to Opponent Hero #" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << currentPlayer[0] << std::setw(colWidth) << currentPlayer[1] << std::setw(colWidth) << currentPlayer[2] << std::setw(colWidth * 2) << currentPlayer[3] << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << opponentPlayer[0] << std::setw(colWidth) << opponentPlayer[1] << std::setw(colWidth) << opponentPlayer[2] << std::setw(colWidth * 2) << opponentPlayer[3] << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << "============================= " << currentPlayer[0] << "'s turn ========================" << std::endl;
}

void Console::displayGameResult(std::vector<std::string> message)
{
}

Console::~Console()
{
}