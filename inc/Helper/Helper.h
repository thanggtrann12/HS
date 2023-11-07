#ifndef HELPER_H
#define HELPER_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cstdarg>
#include <sstream>
#define UNUSED(x) (void)(x)

class Card;
class Hero;

struct GameData_t
{
    std::shared_ptr<Hero> hero;
    std::vector<std::shared_ptr<Card>> tableEntities;
    std::vector<std::shared_ptr<Card>> handEntities;
    std::vector<std::string> stats;
    int turnCount = 0;
};

struct GameStats_t
{
    std::string basicHeroStats;
    std::vector<std::string> stats;
    std::vector<std::string> cardNames;
    std::vector<std::string> cardTypes;
    std::vector<std::string> cardSkills;
    std::vector<std::string> health;
    std::vector<std::string> attack;
    std::vector<std::string> activate;
};

#endif // HELPER_H
