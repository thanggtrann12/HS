// Console.cpp
#include "Console/Console.h"
#include "Game/Game.h"
#include <iostream>
#include <limits>
#include <unistd.h>
#include <termios.h>
#include <iomanip>
#include <chrono>
#include <thread>
Console::Console()
{
    std::cout << "init display" << std::endl;
}
void Console::clearConsole()
{
    system("clear");
}
void Console::displayWelcomeMessage(int &choice)
{
    const int numOptions = 2;
    int currentIndex = 0;
    int key;

    struct termios original_termios;
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    while (1)
    {

        std::cout << "\033[H\033[J";

        std::cout << "=====================================================================" << std::endl;
        std::cout << "#" << std::setw(68) << "#" << std::endl;
        std::cout << "#" << std::setw(68) << "#" << std::endl;
        std::cout << "#                    WELCOME TO MY DAMN GAME                        #" << std::endl;
        std::cout << "#                     Choose option to play                         #" << std::endl;

        for (int i = 1; i <= numOptions; ++i)
        {
            if (i - 1 == currentIndex)
            {
                if (i == 1)
                {
                    std::cout << "#                    >   " << i << ". Host a game    <                        #" << std::endl;
                }
                else if (i == 2)
                {
                    std::cout << "#                    >   " << i << ". Join a game    <                        #" << std::endl;
                }
                else
                {
                    std::cout << "#                        " << i << ". Option " << i << "                           #" << std::endl;
                }
            }
            else
            {
                if (i == 1)
                {
                    std::cout << "#                        " << i << ". Host a game                             #" << std::endl;
                }
                else if (i == 2)
                {
                    std::cout << "#                        " << i << ". Join a game                             #" << std::endl;
                }
                else
                {
                    std::cout << "#                        " << i << ". Option " << i << "                           #" << std::endl;
                }
            }
        }
        std::cout << "#" << std::setw(68) << "#" << std::endl;
        std::cout << "#          Uses ↑ and ↓ to select and Enter to confirm              #" << std::endl;
        std::cout << "#" << std::setw(68) << "#" << std::endl;
        std::cout << "#" << std::setw(68) << "#" << std::endl;
        std::cout << "=====================================================================" << std::endl;

        key = getchar();

        switch (key)
        {
        case 27:
            key = getchar();
            if (key == 91)
            {
                key = getchar();
                if (key == 65 && currentIndex > 0)
                {
                    currentIndex--;
                }
                else if (key == 66 && currentIndex < numOptions - 1)
                {
                    currentIndex++;
                }
            }
            break;
        case 10:
            choice = currentIndex + 1;
            tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
            return;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void Console::displayGameState(std::vector<std::string> currentPlayer, std::vector<std::string> opponentPlayer, std::vector<std::string> message)
{
    clearConsole();
    const int colWidth = 10;
    int leftPadding;
    int rightPadding;
    int padding = 15;
    if (message.size() > 0)
    {
        std::cout << "called" << std::endl;
        std::cout << "================================================================================" << std::endl;
        std::cout << "================================================================================" << std::endl;
        for (int i = 0; i < message.size(); i++)
        {
            leftPadding = (74 - message[i].length() - 4) / 2;
            rightPadding = 74 - leftPadding - message[i].length() - 2;
            std::cout << std::setw(leftPadding) << " " << message[i] << std::setw(rightPadding) << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "================================================================================" << std::endl;
    std::cout << std::left << std::setw(padding) << "Player";
    std::cout << std::left << std::setw(padding) << "Hero HP";
    std::cout << std::left << std::setw(padding) << "Hero Attack";
    std::cout << std::left << std::setw(padding * 1.5) << "Minions Attack";
    std::cout << std::left << std::setw(padding) << "Total Damage" << std::endl;
    std::cout << "================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(padding) << currentPlayer[0];
    std::cout << std::left << std::setw(padding + 5) << currentPlayer[1];
    int totalCrAtk = std::stoi(currentPlayer[3]);
    int minionCrAtk;
    if (totalCrAtk > 0)
    {
        minionCrAtk = std::stoi(currentPlayer[3]) - std::stoi(currentPlayer[2]);
    }
    else
    {
        minionCrAtk = 0;
    }
    std::cout << std::left << std::fixed << std::setprecision(2) << std::setw(padding + 5) << currentPlayer[2];
    std::cout << std::left << std::fixed << std::setprecision(2) << std::setw(padding) << minionCrAtk;
    std::cout << std::left << std::fixed << std::setprecision(2) << std::setw(padding) << currentPlayer[3] << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(padding) << opponentPlayer[0];
    std::cout << std::left << std::setw(padding + 5) << opponentPlayer[1];
    int totalOpAtk = 0;
    int minionOpAtk;
    if (totalOpAtk > 0)
    {
        minionOpAtk = std::stoi(opponentPlayer[3]) - std::stoi(opponentPlayer[2]);
    }
    else
    {
        minionOpAtk = 0;
    }
    std::cout << std::left << std::fixed << std::setprecision(2) << std::setw(padding + 5) << opponentPlayer[2];
    std::cout << std::left << std::fixed << std::setprecision(2) << std::setw(padding) << minionOpAtk;
    std::cout << std::left << std::fixed << std::setprecision(2) << std::setw(padding) << opponentPlayer[3] << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "================================================================================" << std::endl;
    std::cout << "================================================================================" << std::endl;
    waitForEnter();
    clearConsole();
    std::cout << "=========================== Wait for other turn ================================" << std::endl;
}

void Console::displayGameResult(std::vector<std::string> message)
{
}

void Console::waitForEnter()
{
    std::cout << std::setw(20) << " "
              << "Press Enter to continue...";
    int key = getchar();
    if (key == 10)
        return;
}

int Console::displayMenu(const std::string &title, const std::vector<std::string> &menuOptions)
{
    int numOptions = menuOptions.size();
    int currentIndex = 0;
    int key;

    struct termios original_termios;
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    while (1)
    {
        std::cout << "\033[H\033[J";
        int width = 80;
        int height = menuOptions.size() + 4;
        std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;
        int titlePadding = (width - title.length() - 4) / 2;
        std::cout << "|";
        std::cout << std::string(titlePadding, ' ') << "\033[35m" << title << "\033[0m";
        std::cout << std::string(width - title.length() - titlePadding - 2, ' ') << "|" << std::endl;
        std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;
        if (numOptions > 0)
            for (int i = 0; i < numOptions; ++i)
            {
                if (i == currentIndex)
                {
                    std::cout << "| \033[32m-> ";
                }
                else
                {
                    std::cout << "|    ";
                }
                int padding = (width - menuOptions[i].length() - 6) / 2;
                std::cout << std::string(padding, ' ') << menuOptions[i] << std::string(width - menuOptions[i].length() - padding - 6, ' ') << "\033[0m|" << std::endl;
            }
        else
        {
            std::cout << "|              You are ran out of cards, only hero attack!                     |" << std::endl;
        }
        std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;

        key = getchar();

        switch (key)
        {
        case 27:
            key = getchar();
            if (key == 91)
            {
                key = getchar();
                if (key == 65 && currentIndex > 0)
                {
                    currentIndex--;
                }
                else if (key == 66 && currentIndex < numOptions - 1)
                {
                    currentIndex++;
                }
            }
            break;
        case 10:
            tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
            return currentIndex;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    return -1;
}

void Console::loadingConsole()
{
    int total = 100;
    int width = 50;
    int delay = 50;

    std::cout << "              Please waiting when loading resource!" << std::endl;
    for (int i = 0; i <= total; ++i)
    {
        float percentage = static_cast<float>(i) / total * 100;
        int numHashes = static_cast<int>(percentage / 2);
        int numSpaces = width - numHashes;
        std::cout << "\rLoading: [";
        for (int j = 0; j < numHashes; ++j)
        {
            std::cout << "#";
        }
        for (int j = 0; j < numSpaces; ++j)
        {
            std::cout << " ";
        }
        std::cout << "] " << percentage << "%";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << "\n              Done." << std::endl;
}

Console::~Console()
{
}