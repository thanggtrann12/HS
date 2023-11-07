#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
void printTable(const std::string &title, const std::vector<std::string> &tableEntities)
{
    int numStatsPlayer1 = tableEntities.size();

    int width = 173;
    int height = tableEntities.size() + 4;
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    int titlePadding = (width - title.length() - 4) / 2;
    std::cout << "┃";
    std::cout << std::string(titlePadding, ' ') << "\033[35m" << std::left << std::setw(title.length()) << title << "\033[0m";
    std::cout << std::string(width - title.length() - titlePadding - 2, ' ') << "┃" << std::endl;
    std::cout << "┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨" << std::endl;

    if (numStatsPlayer1 > 0)
    {
        for (int i = 0; i < numStatsPlayer1; ++i)
        {
            std::cout << "┃    " << std::left << tableEntities[i] << std::string(width - tableEntities[i].length() - 6, ' ') << "┃" << std::endl;
        }
    }
    else
    {
        std::cout << "┃ " << std::left << std::setw(width - 4) << "No table entities to display."
                  << " ┃" << std::endl;
    }

    std::cout << "┃                                                                                                                                                                           ┃" << std::endl;
    int numStatsPlayer2 = tableEntities.size();
    if (numStatsPlayer2 > 0)
    {
        for (int i = 0; i < numStatsPlayer2; ++i)
        {
            std::cout << "┃    " << std::left << tableEntities[i] << std::string(width - tableEntities[i].length() - 6, ' ') << "┃" << std::endl;
        }
    }
    else
    {
        std::cout << "┃ " << std::left << std::setw(width - 4) << "No table entities to display."
                  << " ┃" << std::endl;
    }
    titlePadding = (width - title.length() - 4) / 2;

    std::cout << "┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨" << std::endl;
    std::cout << "┃";
    std::cout << std::string(titlePadding, ' ') << "\033[35m" << std::left << std::setw(title.length()) << title << "\033[0m";
    std::cout << std::string(width - title.length() - titlePadding - 2, ' ') << "┃" << std::endl;
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
}
int main()
{
    std::vector<std::string> data = {"asdasda", "asdasdasasdasdd"};

    printTable("hello", data);
    return 0;
}