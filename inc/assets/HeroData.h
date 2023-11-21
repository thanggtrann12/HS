#ifndef HERO_DATA_H
#define HERO_DATA_H
#include <iostream>
#include <string>

enum HeroType
{
    BUTCHER,
    SLARK,
    MAX_HERO
};

struct HeroData
{
    std::string name;
    unsigned int attack;
    unsigned int health;
    HeroType type;
};

const HeroData heroes[MAX_HERO] =
    {
        {.name = "Butcher",
         .attack = 6,
         .health = 120,
         .type = BUTCHER},
        {.name = "Slark",
         .attack = 10,
         .health = 72,
         .type = SLARK},
};

#endif // HERO_DATA_H