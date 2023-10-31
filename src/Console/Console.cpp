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
#include "Helper/Helper.h"
Console::Console()
{
  LOG_I("Console display");
}
void Console::clearConsole()
{
  system("clear");
}
void Console::displayWelcomeMessage(int &choice)
{
  const int numOptions = 3;
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
          std::cout << "# \033[33m                   >   " << i << ". Host a game    <                    \033[0m    #" << std::endl;
        }
        else if (i == 2)
        {
          std::cout << "# \033[33m                   >   " << i << ". Join a game    <                    \033[0m    #" << std::endl;
        }
        else if (i == 3)
        {
          std::cout << "# \033[33m                   >   " << i << ". Play offline    <                   \033[0m    #" << std::endl;
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
        else if (i == 3)
        {
          std::cout << "#                        " << i << ". Play offline                            #" << std::endl;
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
      LOG_D("User choice mode %s", std::to_string(choice).c_str());
      tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
      return;
    }
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
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
    int width = 100;
    int height = menuOptions.size() + 4;
    std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;
    int titlePadding = (width - title.length() - 4) / 2;
    std::cout << "|";
    std::cout << std::string(titlePadding, ' ') << "\033[35m" << std::left << std::setw(title.length()) << title << "\033[0m";
    std::cout << std::string(width - title.length() - titlePadding - 2, ' ') << "|" << std::endl;
    std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;

    if (numOptions > 0)
    {
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
        int padding = 5;
        std::cout << std::string(padding, ' ') << std::left << menuOptions[i] << std::string(width - menuOptions[i].length() - padding - 6, ' ') << "\033[0m|" << std::endl;
      }
    }
    else
    {
      std::cout << "| " << std::left << std::setw(width - 4) << "You are ran out of cards, only hero attack!"
                << " |" << std::endl;
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
      LOG_D("[%s] choice card [%s]", title.c_str(), menuOptions[currentIndex].c_str());
      return currentIndex;
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
  return -1;
}

void Console::displayTableStats(const std::string &title, const std::vector<std::string> &tableEntities)
{
  int numOptions = tableEntities.size();

  int width = 120;
  int height = tableEntities.size() + 4;
  std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;
  int titlePadding = (width - title.length() - 4) / 2;
  std::cout << "|";
  std::cout << std::string(titlePadding, ' ') << "\033[35m" << std::left << std::setw(title.length()) << title << "\033[0m";
  std::cout << std::string(width - title.length() - titlePadding - 2, ' ') << "|" << std::endl;
  std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;

  if (numOptions > 0)
  {
    for (int i = 0; i < numOptions; ++i)
    {
      std::cout << "|    " << std::left << tableEntities[i] << std::string(width - tableEntities[i].length() - 6, ' ') << "|" << std::endl;
    }
  }
  else
  {
    std::cout << "| " << std::left << std::setw(width - 4) << "No table entities to display."
              << " |" << std::endl;
  }

  std::cout << '+' << std::string(width - 2, '-') << '+' << std::endl;
}

void Console::loadingConsole()
{
  int total = 100;
  int width = 50;
  int delay = 20;

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
  std::cout << "\n                      Done." << std::endl;
}

std::vector<std::string> splitAndPrintCardSkill(const std::string &cardSkill, int contentWidth)
{
  std::vector<std::string> skillParts;
  if (cardSkill.length() <= contentWidth)
  {
    skillParts.push_back(cardSkill);
  }
  else
  {
    size_t start = 0;

    while (start < cardSkill.length())
    {
      size_t maxPartLength = contentWidth;

      while (maxPartLength > 0 && !isspace(cardSkill[start + maxPartLength - 1]))
      {
        maxPartLength--;
      }

      // Handle the case when maxPartLength becomes 0
      if (maxPartLength == 0)
      {
        maxPartLength = contentWidth;
      }

      std::string skillPart = cardSkill.substr(start, maxPartLength);
      skillParts.push_back(skillPart);

      start += maxPartLength;

      if (start < cardSkill.length() && isspace(cardSkill[start]))
      {
        start++;
      }
    }
  }

  return skillParts;
}

void Console::displayHandEntities(const GameStats_t &data)
{

  int contentWidth = 33;
  int columns = data.cardNames.size();

  for (int i = 0; i < columns; i++)
  {
    std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < columns; i++)
  {
    int padding = (contentWidth - data.cardNames[i].length()) / 2;
    int leftPadding = padding;
    int rightPadding = contentWidth - data.cardNames[i].length() - leftPadding;
    std::cout << "|" << std::setw(leftPadding) << ' ' << data.cardNames[i] << std::setw(rightPadding) << ' ' << "|" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < columns; i++)
  {
    std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < columns; i++)
  {
    std::string cardInfo = data.cardTypes[i] + "  | " + data.activate[i];
    int cardInfoPadding = (contentWidth - cardInfo.length()) / 2;
    std::cout << "|" << std::setw(cardInfoPadding) << ' ' << cardInfo << std::setw(cardInfoPadding) << ' ' << "|" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < columns; i++)
  {
    std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;

  std::vector<std::vector<std::string>> skillColumns(columns);
  for (int i = 0; i < columns; i++)
  {
    skillColumns[i] = splitAndPrintCardSkill(data.cardSkills[i], contentWidth);
  }

  int maxRows = 0;
  for (const auto &column : skillColumns)
  {
    maxRows = std::max(maxRows, static_cast<int>(column.size()));
  }

  for (int row = 0; row < maxRows; row++)
  {
    for (int col = 0; col < columns; col++)
    {
      std::string skillPart = (row < skillColumns[col].size()) ? skillColumns[col][row] : "";
      int padding = (contentWidth - skillPart.length()) / 2;
      int leftPadding = padding;
      int rightPadding = contentWidth - skillPart.length() - leftPadding;
      std::cout << "|" << std::setw(leftPadding) << ' ' << skillPart << std::setw(rightPadding) << ' ' << "|" << std::setw(5) << std::left << " ";
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < columns; i++)
  {
    std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  int hpPosition = (contentWidth - 10) / 2;
  int atkPosition = (contentWidth - 10) / 2 + 10;
  for (int i = 0; i < columns; i++)
  {

    std::cout << "|";
    std::cout << std::setw(hpPosition) << std::right << "HP";
    std::cout << std::setw(atkPosition - hpPosition - 1) << "|";
    std::cout << std::setw(contentWidth - atkPosition - 5) << "ATK";
    std::cout << std::setw(7) << "|" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < columns; i++)
  {
    std::cout << "|";
    std::cout << std::setw(hpPosition - 2) << std::right << "[" << data.health[i] << "]";
    std::cout << std::setw(atkPosition - hpPosition - 1) << "|";
    std::cout << std::setw(contentWidth - atkPosition - 7) << "[" << data.attack[i] << "]";
    std::cout << std::setw(7) << "|" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < columns; i++)
  {
    std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
  }
  std::cout << std::endl;
}

Console::~Console()
{
}