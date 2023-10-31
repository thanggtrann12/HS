#ifndef HELPER_H
#define HELPER_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cstdarg>
#include <sstream>
#define UNUSED(x) (void)(x)

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"
inline void logToFile(int level, size_t line, const char *Fname, const char *input...) {
    std::ofstream logFile(LOG_FILE_PATH, std::ios::app);  // Open in append mode
    va_list args;
    va_start(args, input);
    if (logFile.is_open()) {
        if (level == 0)
            logFile<<"[ "<<  Fname << ":"<< line<<" ] [DEBUG]" ;
        if (level == 1)
            logFile<<"[ "<<  Fname << ":"<< line<<" ] [WARN]" ;
        if (level == 2)
            logFile<<"[ "<<  Fname << ":"<< line<<" ] [FATAL]" ;
        if (level == 3)
            logFile<<"[ "<<  Fname << ":"<< line<<" ] [INFO]" ;
        }
    for (const char *i = input; *i != 0; ++i)
    {
        if (*i != '%') {
            logFile << *i;
            continue;
        }
        switch (*(++i)) {
            case '%':
                logFile << '%';
                break;
            case 's':
                logFile << va_arg(args, const char *);
                break;
            case 'd':
                logFile << va_arg(args, int);
                break;
        }
    }
    logFile<<"\n";
    logFile.close();
}
#define LOG_D(...) logToFile(0, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_W(...) logToFile(1, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_F(...) logToFile(2, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_I(...) logToFile(3, __LINE__, __FILE__, __VA_ARGS__)




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


#endif // HELPER_H
