#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <memory>
#include <vector>
#include <string>

#define UNUSED(x) (void)(x)

class Minion;
class Hero;

struct GameData_t
{
    std::shared_ptr<Hero> hero;
    std::vector<std::shared_ptr<Minion>> tableEntities;
    std::vector<std::shared_ptr<Minion>> handEntities;
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

#endif // GAME_DATA_H
