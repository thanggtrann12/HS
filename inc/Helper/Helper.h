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

#endif // HELPER_H
