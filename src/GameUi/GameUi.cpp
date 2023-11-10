#include "GameUi/GameUi.h"
#include "Helper/Helper.h"
#include "CardManager/CardFactory/Card.h"
#include "CardManager/Hero.h"
#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
#include <termios.h>
#include <iomanip>
#include <chrono>
#include <thread>
GameUi::GameUi()
{
    std::cout << "Init game ui" << std::endl;
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

void GameUi::GameUi_updateGameState(player_t player, int state, int &cardChoiced, const std::vector<GameData_t> &tableData)
{
    switch (state)
    {
    case INIT:
        GameUi_displayModesOption(cardChoiced);
        break;
    case CHOICE:
        GameUi_displayHandCard(cardChoiced, tableData[player].hero->getName(), tableData[player].handCard);
        break;
    case STATS:
        GameUi_prepareConsole();
        GameUi_displayEntireTable(tableData);
        break;
    case WAIT_CONFIRM:
        GameUi_waitForConfirm();
        break;
    case WAIT_NEXT_TURN:
        GameUi_waitForNextTurn();
        break;
    case RESULT:
        GameUi_displayResult(tableData);
        break;
    }
}

void GameUi::GameUi_waitForConfirm()
{
    std::cout << std::string(120, ' ') << "Press Enter to continue ....";
    int key = getchar();
    if (key == 10)
        return;
}

void GameUi::GameUi_waitForNextTurn()
{
    std::cout << std::string(120, ' ') << "Please wait for other turn..." << std::endl;
}

void GameUi::GameUi_prepareConsole()
{
    system("clear");
}

void GameUi::GameUi_displayEntireTable(const std::vector<GameData_t> &tableData)
{
    std::vector<std::vector<std::vector<std::string>>> GameData(2);
    std::vector<std::vector<std::vector<std::string>>> playerMsg(2);
    std::vector<std::vector<std::vector<std::string>>> firstGroup(2);
    std::vector<std::vector<std::vector<std::string>>> secondGroup(2);
    for (int player = 0; player < 2; player++)
    {
        if (!tableData[player].tableEntities.empty())
        {
            for (auto &entity : tableData[player].tableEntities)

            {
                if (entity->getCardType() == Card::CardType::FIRELORD || entity->getCardType() == Card::CardType::THALNOS)
                {
                    card_template_t templ = GameUi_getTemplateWithText("\033[36m", CARD_TEMPLATE_MINION_NO_ABILITY, entity->getName(), entity->getAttack(), entity->getHP(), entity->getSkill(), "");
                    GameData[player].emplace_back(templ);
                }
                else
                {
                    card_template_t templS = GameUi_getTemplateWithText("\033[33m", CARD_TEMPLATE_MINION_WITH_ABILITY, entity->getName(), entity->getAttack(), entity->getHP(), entity->getSkill(), "ACTIVE");
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
    std::vector<std::string> statsOfPlayer1;
    for (auto &e : tableData[0].stats)
    {
        statsOfPlayer1.push_back(e + ' ');
    }
    std::vector<std::string> statsOfPlayer2;
    for (auto &e : tableData[1].stats)
    {
        statsOfPlayer2.push_back(e + ' ');
    }
    std::cout << std::string(50, ' ') << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (unsigned int i = 0; i < 177; i++)
    {
        std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

    GameUi_displayCard(firstGroup[0]);
    GameUi_displayCard(secondGroup[0]);
    GameUi_getCenterTemplateWithMessage(tableData);
    GameUi_displayCard(firstGroup[1]);
    GameUi_displayCard(secondGroup[1]);

    std::cout << std::string(50, ' ') << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (unsigned int i = 0; i < 177; i++)
    {
        std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

void GameUi::GameUi_displayCard(std::vector<std::vector<std::string>> &hand)
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
            std::cout << std::string(50, ' ') << EXTERNAL_BORDER_CHAR_UP_DOWN << "  ";
            for (const std::vector<std::string> &row : hand)
            {
                if (i < row.size())
                {
                    std::cout << row[i] << "  ";
                }
            }
            std::cout << std::string(35 * (5 - hand.size()), ' ');
            std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << "  " << std::endl;
        }
    }
}

void GameUi::GameUi_replaceTextFromLeftSide(card_template_t &text, char flag, std::string new_text)
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

void GameUi::GameUi_replaceTextFromRightSide(card_template_t &text, char flag, std::string new_text)
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

void GameUi::GameUi_prepareForReplace(card_template_t &text)
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

card_template_t GameUi::GameUi_getTemplateWithText(const std::string &color, card_template_t out, std::string name, int attack, int health, std::string skill, std::string status)
{
    std::ostringstream oss;
    GameUi_prepareForReplace(out);
    for (int i = 0; i < out.size(); i++)
    {
        out[i] = color + out[i] + "\033[0m";
    }
    GameUi_replaceTextFromLeftSide(out, 'N', name);
    GameUi_replaceTextFromRightSide(out, 'S', status);
    oss.str("");
    oss << attack;
    GameUi_replaceTextFromLeftSide(out, 'A', oss.str());
    oss.str("");
    oss << health;
    GameUi_replaceTextFromRightSide(out, 'H', oss.str());
    GameUi_replaceTextFromLeftSide(out, 'K', skill);
    oss.str("");
    return out;
}

void GameUi::GameUi_getCenterTemplateWithMessage(const std::vector<GameData_t> &tableData)
{
    std::vector<std::string> player1Stats = tableData[0].stats;
    std::vector<std::string> player2Stats = tableData[1].stats;
    std::string title = tableData[0].hero->getName() + " HP[" + std::to_string(tableData[0].hero->getHP()) + "] ATK[" + std::to_string(tableData[0].hero->getAttack()) + "]";
    int numStatsPlayer1 = player1Stats.size();

    int width = 179;
    std::cout << std::string(50, ' ') << "┃  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓  ┃" << std::endl;
    int titlePadding = (width - title.length() - 4) / 2;
    std::cout << std::string(50, ' ') << "┃  ┃";
    std::cout << std::string(titlePadding, ' ') << "\033[33m" << std::left << std::setw(title.length()) << title << "\033[0m";
    std::cout << std::string(width - title.length() - titlePadding - 8, ' ') << "┃  ┃" << std::endl;
    std::cout << std::string(50, ' ') << "┃  ┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨  ┃" << std::endl;

    if (numStatsPlayer1 > 0)
    {
        for (int i = 0; i < numStatsPlayer1; ++i)
        {
            std::cout << std::string(50, ' ') << "┃  ┃    " << std::left << player1Stats[i] << std::string(width - player1Stats[i].length() - 12, ' ') << "┃  ┃" << std::endl;
        }
    }

    std::cout << std::string(50, ' ') << "┃  ┃                                                                                                                                                                           ┃  ┃" << std::endl;
    int numStatsPlayer2 = player2Stats.size();
    if (numStatsPlayer2 > 0)
    {
        for (int i = 0; i < numStatsPlayer2; ++i)
        {
            std::cout << std::string(50, ' ') << "┃  ┃    " << std::left << player2Stats[i] << std::string(width - player2Stats[i].length() - 12, ' ') << "┃  ┃" << std::endl;
        }
    }
    title.clear();
    title = tableData[1].hero->getName() + " HP[" + std::to_string(tableData[1].hero->getHP()) + "] ATK[" + std::to_string(tableData[1].hero->getAttack()) + "]";
    titlePadding = (width - title.length() - 4) / 2;

    std::cout << std::string(50, ' ') << "┃  ┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨  ┃" << std::endl;
    std::cout << std::string(50, ' ') << "┃  ┃";
    std::cout << std::string(titlePadding, ' ') << "\033[33m" << std::left << std::setw(title.length()) << title << "\033[0m";
    std::cout << std::string(width - title.length() - titlePadding - 8, ' ') << "┃  ┃" << std::endl;
    std::cout << std::string(50, ' ') << "┃  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛  ┃" << std::endl;
}

void GameUi::GameUi_displayGameRules()
{
    for (auto &e : GAME_RULES)
    {
        std::cout << std::string(50, ' ') << e << std::endl;
    }
}

void GameUi::GameUi_displayModesOption(int &option)
{
    const int numOptions = 4;
    int currentIndex = 0;
    int key;

    struct termios original_termios;
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    while (1)
    {

        std::cout << "\033[H\033[J \n\n\n\n\n\n\n\n";

        std::cout << std::string(100, ' ') << "=====================================================================" << std::endl;
        std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
        std::cout << std::string(100, ' ') << "#" << std::setw(68) << "#" << std::endl;
        std::cout << std::string(100, ' ') << "#              WELCOME TO MY COPY HEARTH STONE GAME                 #" << std::endl;
        std::cout << std::string(100, ' ') << "#                     Choose option to play                         #" << std::endl;

        for (int i = 1; i <= numOptions; ++i)
        {
            if (i - 1 == currentIndex)
            {
                if (i == 1)
                {
                    std::cout << std::string(100, ' ') << "# \033[33m                   →   " << i << ". Host a game    ←                    \033[0m    #" << std::endl;
                }
                else if (i == 2)
                {
                    std::cout << std::string(100, ' ') << "# \033[33m                   →   " << i << ". Join a game    ←                    \033[0m    #" << std::endl;
                }
                else if (i == 3)
                {
                    std::cout << std::string(100, ' ') << "# \033[33m                   →   " << i << ". Play offline    ←                   \033[0m    #" << std::endl;
                }
                else if (i == 4)
                {
                    std::cout << std::string(100, ' ') << "# \033[33m                   →   " << i << ". Read Game Rules ←                   \033[0m    #" << std::endl;
                }
            }
            else
            {
                if (i == 1)
                {
                    std::cout << std::string(100, ' ') << "#                        " << i << ". Host a game                             #" << std::endl;
                }
                else if (i == 2)
                {
                    std::cout << std::string(100, ' ') << "#                        " << i << ". Join a game                             #" << std::endl;
                }
                else if (i == 3)
                {
                    std::cout << std::string(100, ' ') << "#                        " << i << ". Play offline                            #" << std::endl;
                }
                else if (i == 4)
                {
                    std::cout << std::string(100, ' ') << "#                       " << i << ". Read Game Rules                          #" << std::endl;
                }
            }
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
            option = currentIndex + 1;
            if (option == 4)
            {
                GameUi_displayGameRules();
                GameUi_waitForConfirm();
                GameUi_displayModesOption(option);
            }
            tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
            return;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void GameUi::GameUi_displayHandCard(int &choice, const std::string &name, const std::vector<std::shared_ptr<Card>> &handCard)
{
    std::vector<std::string> menuOptions;
    for (auto &e : handCard)
    {
        menuOptions.push_back(e->getDesciption());
    }
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
        std::cout << "\033[H\033[J \n\n\n\n";
        int width = 100;
        int height = menuOptions.size() + 4;
        std::vector<std::vector<std::string>> card;
        std::vector<std::vector<std::string>> firstGroup;
        std::vector<std::vector<std::string>> secondGroup;
        card_template_t temp;
        std::cout<<std::string(width+30, ' ')<<name<<"'s turn"<<std::endl;
        for (int cardIndex = 0; cardIndex < handCard.size(); cardIndex++)
        {
            if (currentIndex == cardIndex)
            {
                if (handCard[currentIndex]->getCardType() == Card::CardType::FIRELORD || handCard[currentIndex]->getCardType() == Card::CardType::THALNOS || handCard[currentIndex]->getCardType() == Card::CardType::TECHIES)
                {
                    temp = GameUi_getTemplateWithText("\033[36m", CARD_TEMPLATE_MINION_NO_ABILITY, handCard[currentIndex]->getName(), handCard[currentIndex]->getAttack(), handCard[currentIndex]->getHP(), handCard[currentIndex]->getSkill(), "");
                }
                else
                {
                    temp = GameUi_getTemplateWithText("\033[33m", CARD_TEMPLATE_MINION_WITH_ABILITY, handCard[currentIndex]->getName(), handCard[currentIndex]->getAttack(), handCard[currentIndex]->getHP(), handCard[currentIndex]->getSkill(), "INACTIVE");
                }
                card.emplace_back(temp);
            }
            else
            {
                if (handCard[cardIndex]->getCardType() == Card::CardType::FIRELORD || handCard[cardIndex]->getCardType() == Card::CardType::THALNOS || handCard[cardIndex]->getCardType() == Card::CardType::TECHIES)
                {
                    temp = GameUi_getTemplateWithText("\033[0m", CARD_TEMPLATE_MINION_NO_ABILITY, handCard[cardIndex]->getName(), handCard[cardIndex]->getAttack(), handCard[cardIndex]->getHP(), handCard[cardIndex]->getSkill(), "");
                }
                else
                {
                    temp = GameUi_getTemplateWithText("\033[0m", CARD_TEMPLATE_MINION_WITH_ABILITY, handCard[cardIndex]->getName(), handCard[cardIndex]->getAttack(), handCard[cardIndex]->getHP(), handCard[cardIndex]->getSkill(), "INACTIVE");
                }
                card.emplace_back(temp);
            }
        }
        std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> splitResult = splitVector(card);
        firstGroup = splitResult.first;
        secondGroup = splitResult.second;
        splitResult.first.clear();
        splitResult.second.clear();
        std::cout << std::string(50, ' ') << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        for (unsigned int i = 0; i < 177; i++)
        {
            std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
        std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;
        GameUi_displayCard(firstGroup);
        GameUi_displayCard(secondGroup);
        std::cout << std::string(50, ' ') << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
        for (unsigned int i = 0; i < 177; i++)
        {
            std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
        std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
        std::cout << std::string(width+20, ' ') << "Uses → and ← to select and Enter to confirm" << std::endl;
        key = getchar();

        switch (key)
        {
        case 27:
            key = getchar();
            if (key == 91)
            {
                key = getchar();
                if (key == 68 && currentIndex > 0)
                {
                    currentIndex--;
                }
                else if (key == 67 && currentIndex < numOptions - 1)
                {
                    currentIndex++;
                }
            }
            break;
        case 10:
            tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
            choice = currentIndex;
            return;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    return;
}

void GameUi::GameUi_displayResult(const std::vector<GameData_t> &tableData)
{

    auto printWinnerMessages = [](const std::vector<std::string> &winnerMessages)
    {
        for (const auto &e : winnerMessages)
        {
            std::cout << std::string(50, ' ') << e << std::endl;
        };
    };
    for (int player = 0; player < tableData.size(); player++)
    {
        if (!tableData[player].hero->IsAlive())
        {
            const auto &winnerMessages =
                (tableData[1 - player].hero->getName() == "Slark") ? HERO_SLARK_WINNER : HERO_BUTCHER_WINNER;
            GameUi_prepareConsole();
            printWinnerMessages(winnerMessages);
            std::cout << std::string(120, ' ') << "Congrat player " << player + 1 << " is WINNER" << std::endl;
            GameUi_waitForConfirm();
            system("exit");
        }
    }
}