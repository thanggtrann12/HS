#ifndef CARD_DATA_H
#define CARD_DATA_H
#include <iostream>
#include <string>

typedef enum
{
    FIRELORD,
    THALNOS,
    SHAMAN,
    BRAWL,
    TECHIES,
    MAX_TYPE

} CardType;

struct CardData
{
    std::string name;
    unsigned int attack;
    unsigned int health;
    std::string skill;
    CardType type;
};

const CardData cardsData[MAX_TYPE] =
    {
        {"Ragnaros the Firelord", 3, 1, "No Skill", FIRELORD},
        {"Bloodmage Thalnos", 1, 1, "No Skill", THALNOS},
        {"Flametongue Totem", 0, 3, "Provides all alliance  minions with a +1 Attack bonus.", SHAMAN},
        {"Brawl", 0, 0, "Destroy a random minion of the opposite player", BRAWL},
        {"Techies", 1, 3, "On dead, deals 3 damage to both hero", TECHIES},
};

#endif