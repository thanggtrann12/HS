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
    std::vector<std::shared_ptr<Card>> handCard;
    std::vector<std::string> stats;
    int turnCount = 0;
    int shamanCout = 0;
};

typedef enum
{
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    MASTER
} player_t;
#endif // HELPER_H
