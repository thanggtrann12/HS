#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
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

void printCardInfo(std::vector<std::string> &cardName, std::vector<std::string> &cardType, std::vector<std::string> &cardSkills, std::vector<int> health, std::vector<int> attack, std::vector<bool> activate)
{
    int contentWidth = 33;
    int columns = cardSkills.size();

    for (int i = 0; i < columns; i++)
    {
        std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < columns; i++)
    {
        int padding = (contentWidth - cardName[i].length()) / 2;
        int leftPadding = padding;
        int rightPadding = contentWidth - cardName[i].length() - leftPadding;
        std::cout << "|" << std::setw(leftPadding) << ' ' << cardName[i] << std::setw(rightPadding) << ' ' << "|" << std::setw(5) << std::left << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < columns; i++)
    {
        std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < columns; i++)
    {
        std::string cardInfo = cardType[i] + " | " + (activate[i] ? "ACTIVATE" : "INACTIVATE");
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
        skillColumns[i] = splitAndPrintCardSkill(cardSkills[i], contentWidth);
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
        std::cout << std::setw(hpPosition - 2) << std::right << "[" << health[i] << "]";
        std::cout << std::setw(atkPosition - hpPosition - 1) << "|";
        std::cout << std::setw(contentWidth - atkPosition - 7) << "[" << attack[i] << "]";
        std::cout << std::setw(7) << "|" << std::setw(5) << std::left << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < columns; i++)
    {
        std::cout << "+" << std::string(contentWidth, '-') << "+" << std::setw(5) << std::left << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> cardNames = {
        "Ragnaros the Firelord",
        "Bloodmage Thalnos",
        "Bloodmage Thalnos",
        "Bloodmage Thalnos",
        "Flametongue Totem"};

    std::vector<std::string> cardTypes = {
        "MINION",
        "MINION",
        "MINION",
        "MINION",
        "SHAMAN"};

    std::vector<std::string> cardSkills = {
        "A minion with normal attack",
        "A minion with normal attack",
        "A minion with normal attack",
        "A minion with normal attack",
        "Provides all alliance minions with a +1 Attack bonus"};

    std::vector<int> health = {2, 3, 4, 3, 2};
    std::vector<int> attack = {1, 2, 3, 0, 5};
    std::vector<bool> activate = {true, true, true, true, false};

    // Print the card information for the cards in the vector
    printCardInfo(cardNames, cardTypes, cardSkills, health, attack, activate);

    return 0;
}