#include "UI/Ui.h"
#include <string>
#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
#include <termios.h>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include "assets/CardData.h"
#include "Player/Player.h"
Ui::Ui()
{
  std::cout << "Wait for checking env!! \nDone." << std::endl;
}
void waitForConfirm()
{
  std::cout << std::string(120, ' ') << "Press Enter to continue ....";
  int key = getchar();
  if (key == 10)
    return;
}
void Ui::updateUiOnState(UiState state, std::vector<Player> &players, unsigned int playerId, unsigned int &clone)
{
  switch (state)
  {
  case INIT:
    displayMenuScreen(clone);
    break;
  case CHOICE_CARD:
    // displayPlayerCard(players[playerId], clone);
    selectCard(players[playerId], clone);
    break;
  case WAIT_NEXT_TURN:
    std::cout << std::string(120, ' ') << "Please wait for other turn..." << std::endl;
    break;
  case WAIT_FOR_CONFIRM:
    waitForConfirm();
    break;
  case UPDATE_BATTLE:
    displayBattle(players, playerId);
    break;
  case RESULT:
    displayResult(players[playerId]);
    break;

  default:
    break;
  }
}

void setTerminalAttributes(struct termios &original_termios, struct termios &new_termios)
{
  tcgetattr(STDIN_FILENO, &original_termios);
  new_termios = original_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void restoreTerminalAttributes(const struct termios &original_termios)
{
  tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void printMenuOption(const std::string &option, bool isSelected)
{
  std::cout << std::string(100, ' ') << "# ";
  if (isSelected)
  {
    std::cout << "\033[33m →    ";
  }
  else
  {
    std::cout << "      ";
  }
  std::cout << std::setw(20) << " " << option << std::setw(20 - option.length()) << "\033[0m" << std::setw(25) << " #" << std::endl;
}

void Ui::displayMenuScreen(unsigned int &choicedMode)
{
  const int numOptions = 4;
  int currentIndex = 0;
  int key;

  struct termios original_termios, new_termios;
  setTerminalAttributes(original_termios, new_termios);

  while (true)
  {
    std::cout << "\033[H\033[J \n\n\n\n\n\n\n\n";
    std::cout << std::string(100, ' ') << "=====================================================================" << std::endl;
    std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
    std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
    std::cout << std::string(100, ' ') << "#              WELCOME TO MY COPY HEARTH STONE GAME                 #" << std::endl;
    std::cout << std::string(100, ' ') << "#                     Choose option to play                         #" << std::endl;

    const std::string menuOptions[] = {
        "Host a game",
        "Join a game",
        "Play offline",
        "Read Game Rules"};

    for (int i = 1; i <= numOptions; ++i)
    {
      bool isSelected = (i - 1 == currentIndex);
      printMenuOption(menuOptions[i - 1], isSelected);
    }

    std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
    std::cout << std::string(100, ' ') << "#          Uses ↑ and ↓ to select and Enter to confirm              #" << std::endl;
    std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
    std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
    std::cout << std::string(100, ' ') << "=====================================================================" << std::endl;

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
      choicedMode = currentIndex + 1;
      std::cout << choicedMode << std::endl;
      restoreTerminalAttributes(original_termios);
      return;
    }
  }
  restoreTerminalAttributes(original_termios);
}

template <typename T>
std::pair<std::vector<T>, std::vector<T>> splitVector(const std::vector<T> &inputVector)
{
  std::pair<std::vector<T>, std::vector<T>> result;
  size_t middle = (inputVector.size() > 5 ? 5 : inputVector.size());
  auto begin1 = inputVector.begin();
  auto end1 = begin1 + middle;
  auto begin2 = end1;
  auto end2 = inputVector.end();

  result.first = std::vector<T>(begin1, end1);
  result.second = std::vector<T>(begin2, end2);

  return result;
}

void displayCard(std::vector<std::vector<std::string>> &hand)
{
  size_t maxRows = 0;
  if (!hand.empty())
  {
    for (const std::vector<std::string> &row : hand)
    {
      if (row.size() > maxRows)
      {
        maxRows = row.size();
      }
    }
    for (size_t i = 0; i < maxRows; i++)
    {
      std::cout << std::string(50, ' ');
      for (const std::vector<std::string> &row : hand)
      {
        if (i < row.size())
        {
          std::cout << row[i] << "  ";
        }
      }
      std::cout << std::string(35 * (5 - hand.size()), ' ');
      std::cout << std::endl;
    }
  }
}

void replaceTextFromLeftSide(card_template_t &text, char flag, std::string new_text)
{
  std::string::iterator sit = new_text.begin();
  bool start_replace = false;
  bool end_replace = false;
  for (card_template_t::iterator vit = text.begin(); vit != text.end(); ++vit)
  {
    for (std::string::iterator lit = vit->begin(); lit != vit->end(); ++lit)
    {
      if (*lit == DELIMITER && *(lit + 1) == flag)
      {
        start_replace = true;
      }
      else if (*lit == DELIMITER)
      {
        end_replace = true;
      }
      if (start_replace && (*lit == flag || *lit == DELIMITER))
      {
        if (sit != new_text.end())
        {
          *lit = *sit;
          ++sit;
        }
        else
        {
          *lit = ' ';
        }
      }
      if (end_replace)
      {
        end_replace = false;
        start_replace = false;
      }
    }
  }
}

void replaceTextFromRightSide(card_template_t &text, char flag, std::string new_text)
{
  std::string::reverse_iterator sit = new_text.rbegin();
  bool start_replace = false;
  bool end_replace = false;
  for (card_template_t::reverse_iterator vit = text.rbegin(); vit != text.rend(); ++vit)
  {
    for (std::string::reverse_iterator lit = vit->rbegin(); lit != vit->rend(); ++lit)
    {
      if (*lit == DELIMITER && *(lit + 1) == flag)
      {
        start_replace = true;
      }
      else if (*lit == DELIMITER)
      {
        end_replace = true;
      }
      if (start_replace && (*lit == flag || *lit == DELIMITER))
      {
        if (sit != new_text.rend())
        {
          *lit = *sit;
          ++sit;
        }
        else
        {
          *lit = ' ';
        }
      }
      if (end_replace)
      {
        end_replace = false;
        start_replace = false;
      }
    }
  }
}

void prepareForReplace(card_template_t &text)
{
  for (card_template_t::iterator it = text.begin(); it != text.end(); ++it)
  {
    for (std::string::iterator sit = it->begin(); sit != it->end(); ++sit)
    {
      if (*sit == '~')
        *sit = DELIMITER;
    }
  }
}
card_template_t getTemplateWithText(const std::string &color, card_template_t out, std::string name, int attack, int health, std::string skill, std::string status)
{
  std::ostringstream oss;
  prepareForReplace(out);
  for (int i = 0; i < out.size(); i++)
  {
    out[i] = color + out[i] + "\033[0m";
  }
  replaceTextFromLeftSide(out, 'N', name);
  replaceTextFromRightSide(out, 'S', status);
  oss.str("");
  oss << attack;
  replaceTextFromLeftSide(out, 'A', oss.str());
  oss.str("");
  oss << health;
  replaceTextFromRightSide(out, 'H', oss.str());
  replaceTextFromLeftSide(out, 'K', skill);
  oss.str("");
  return out;
}

void Ui::displayPlayerCard(Player &player, unsigned int &choicedCard)
{
  selectCard(player, choicedCard);
}

void Ui::selectCard(Player &player, unsigned int &choicedCard)
{
  int currentIndex = 0;
  int key;

  struct termios original_termios;
  tcgetattr(STDIN_FILENO, &original_termios);
  struct termios new_termios = original_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  auto &playerHandCard = player.getHand();
  int temp;
  while (1)
  {
    displayCardList(playerHandCard, currentIndex);
    std::cout << std::string(110, ' ') << player.getBasicInfo() << "'s turn" << std::endl;
    std::cout << std::string(110, ' ') << "Uses ← and → to select and Enter to confirm" << std::endl;

    key = getchar();

    switch (key)
    {
    case 27:
      key = getchar();
      if (key == 91)
      {
        key = getchar();
        const int LEFT_ARROW_KEY = 68;
        const int RIGHT_ARROW_KEY = 67;

        if (key == LEFT_ARROW_KEY && currentIndex > 0)
        {
          currentIndex--;
        }
        else if (key == RIGHT_ARROW_KEY && currentIndex < playerHandCard.size() - 1)
        {
          currentIndex++;
        }
      }
      break;
    case 10:
      tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
      choicedCard = currentIndex;
      return;
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void Ui::displayCardList(std::vector<std::shared_ptr<Card>> &playerHandCard, int currentIndex)
{
  if (playerHandCard.empty())
  {
    std::cerr << "playerHandCard is empty." << std::endl;
    return;
  }

  // Check if currentIndex is within valid range
  if (currentIndex < 0 || currentIndex >= static_cast<int>(playerHandCard.size()))
  {
    std::cerr << "Invalid currentIndex: " << currentIndex << std::endl;
    return;
  }

  std::cout << "\033[H\033[J \n\n\n\n";

  std::vector<std::vector<std::string>> cardLists;
  card_template_t cardHolder;

  for (int cardIndex = 0; cardIndex < static_cast<int>(playerHandCard.size()); cardIndex++)
  {
    if (currentIndex == cardIndex)
    {
      // Ensure currentIndex is within bounds
      if (currentIndex >= 0 && currentIndex < static_cast<int>(playerHandCard.size()))
      {
        cardHolder = getTemplateWithText("\033[36m", CARD_TEMPLATE_MINION_NO_ABILITY,
                                         playerHandCard[currentIndex]->getName(),
                                         playerHandCard[currentIndex]->getAttack(),
                                         playerHandCard[currentIndex]->getHP(),
                                         playerHandCard[currentIndex]->getSkill(), "");
      }
      else
      {
        std::cerr << "Invalid currentIndex: " << currentIndex << std::endl;
        return;
      }
    }
    else
    {
      // Ensure cardIndex is within bounds
      if (cardIndex >= 0 && cardIndex < static_cast<int>(playerHandCard.size()))
      {
        cardHolder = getTemplateWithText("\033[0m", CARD_TEMPLATE_MINION_NO_ABILITY,
                                         playerHandCard[cardIndex]->getName(),
                                         playerHandCard[cardIndex]->getAttack(),
                                         playerHandCard[cardIndex]->getHP(),
                                         playerHandCard[cardIndex]->getSkill(), "");
      }
      else
      {
        std::cerr << "Invalid cardIndex: " << cardIndex << std::endl;
        return;
      }
    }
    cardLists.emplace_back(cardHolder);
  }

  std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> splitResult = splitVector(cardLists);
  std::vector<std::vector<std::string>> firstGroup = splitResult.first;
  std::vector<std::vector<std::string>> secondGroup = splitResult.second;

  displayCard(firstGroup);
  displayCard(secondGroup);
}

void Ui::displayBattle(std::vector<Player> &players, unsigned int playerId)
{
  std::cout << "\033[H\033[J \n\n\n\n";
  auto &currentPlayer = players[playerId];
  auto &opponentPlayer = players[1 - playerId];
  int width = 179;
  int titlePadding = (width - currentPlayer.getBasicInfo().length() - 4) / 2;
  std::vector<std::vector<std::vector<std::string>>> GameData(2);
  std::vector<std::vector<std::vector<std::string>>> playerMsg(2);
  std::vector<std::vector<std::vector<std::string>>> firstGroup(2);
  std::vector<std::vector<std::vector<std::string>>> secondGroup(2);
  for (int player = 0; player < 2; player++)
  {
    if (!players[player].getBattle().empty())
    {
      for (auto &entity : players[player].getBattle())

      {
        if (entity->getCardType() == CardType::FIRELORD || entity->getCardType() == CardType::THALNOS)
        {
          card_template_t templ = getTemplateWithText("\033[36m", CARD_TEMPLATE_MINION_NO_ABILITY, entity->getName(), entity->getAttack(), entity->getHP(), entity->getSkill(), "");
          GameData[player].emplace_back(templ);
        }
        else
        {
          card_template_t templS = getTemplateWithText("\033[33m", CARD_TEMPLATE_MINION_WITH_ABILITY, entity->getName(), entity->getAttack(), entity->getHP(), entity->getSkill(), "ACTIVE");
          GameData[player].emplace_back(templS);
        }
      }
    }
    std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> splitResult = splitVector(GameData[player]);
    firstGroup[player] = splitResult.first;
    secondGroup[player] = splitResult.second;
    splitResult.first.clear();
    splitResult.second.clear();
  }

  auto printBorder = [&](bool isTop)
  {
    std::cout << std::string(50, ' ') << "   " << ((isTop == true) ? EXTERNAL_BORDER_CHAR_TOP_LEFT : EXTERNAL_BORDER_CHAR_BOTTOM_LEFT);
    for (int i = 0; i < 171; i++)
    {
      std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    std::cout << ((isTop == true) ? EXTERNAL_BORDER_CHAR_TOP_RIGHT : EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT) << std::endl;
  };

  auto printTitle = [&](const std::string &title)
  {
    std::cout << std::string(50, ' ') << "   " << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::string(titlePadding, ' ') << "\033[33m" << std::left << std::setw(title.length()) << title << "\033[0m";
    std::cout << std::string(width - title.length() - titlePadding - 8, ' ') << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
  };

  auto printStats = [&](const std::vector<std::string> &stats)
  {
    int numStats = stats.size();
    if (numStats > 0)
    {
      for (int i = 0; i < numStats; ++i)
      {
        std::cout << std::string(50, ' ') << "         " << std::left << stats[i] << std::string(width - stats[i].length() - 12, ' ') << std::endl;
      }
    }
  };
  displayCard(firstGroup[playerId]);
  displayCard(secondGroup[playerId]);
  printBorder(true);
  printTitle(currentPlayer.getBasicInfo());
  printBorder(false);
  printStats(currentPlayer.stats);

  printStats(opponentPlayer.stats);
  printBorder(true);
  printTitle(opponentPlayer.getBasicInfo());
  printBorder(false);
  displayCard(firstGroup[1 - playerId]);
  displayCard(secondGroup[1 - playerId]);
}

void Ui::displayResult(Player &player)
{
  auto printWinnerMessages = [](const std::vector<std::string> &winnerMessages)
  {
    std::cout << "\033[H\033[J \n\n\n\n";
    for (const auto &e : winnerMessages)
    {
      std::cout << std::string(50, ' ') << e << std::endl;
    };
  };
  const auto &winnerMessages =
      (player.getHero()->getType() == SLARK) ? HERO_SLARK_WINNER : HERO_BUTCHER_WINNER;

  printWinnerMessages(winnerMessages);
  std::cout << std::string(120, ' ') << "CONGRATULATION PLAYER " << player.getId() + 1 << " IS WINNER" << std::endl;
  exit(0);
}

Ui::~Ui()
{
}