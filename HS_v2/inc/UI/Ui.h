#ifndef UI_H
#define UI_H
#include <string>
#include <vector>
#include <memory>
class Card;
typedef std::vector<std::string> card_template_t;
const std::string EXTERNAL_BORDER_CHAR_UP_DOWN = "┃";
const std::string EXTERNAL_BORDER_CHAR_LEFT_RIGHT = "━";
const std::string EXTERNAL_BORDER_CHAR_TOP_LEFT = "┏";
const std::string EXTERNAL_BORDER_CHAR_TOP_RIGHT = "┓";
const std::string EXTERNAL_BORDER_CHAR_BOTTOM_LEFT = "┗";
const std::string EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT = "┛";
const std::string EXTERNAL_BORDER_CHAR_MID_LEFT = "┠";
const std::string EXTERNAL_BORDER_CHAR_MID_RIGHT = "┨";

const char DELIMITER = '\v';
const card_template_t CARD_TEMPLATE_MINION_WITH_ABILITY = {
    "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
    "┃    ~NNNNNNNNNNNNNNNNNNNNN~    ┃",
    "┠───────────────────────────────┨",
    "┃         ~SSSSSSSSS~           ┃",
    "┠───────────────────────────────┨",
    "┃   ~KKKKKKKKKKKKKKKKKKKKKK     ┃",
    "┃   KKKKKKKKKKKKKKKKKKKKKKKKK   ┃",
    "┃              KKK~             ┃",
    "┠─ATK─┐                   ┌──HP─┨",
    "┃  ~A~│                   │~H~  ┃",
    "┗━━━━━┷━━━━━━━━━━━━━━━━━━━┷━━━━━┛"};

const card_template_t CARD_TEMPLATE_MINION_NO_ABILITY = {
    "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
    "┃    ~NNNNNNNNNNNNNNNNNNNNN~    ┃",
    "┠───────────────────────────────┨",
    "┃             Minion            ┃",
    "┠───────────────────────────────┨",
    "┃   ~KKKKKKKKKKKKKKKKKKKKKK     ┃",
    "┃   KKKKKKKKKKKKKKKKKKKKKKKKK   ┃",
    "┃              KKKKK~           ┃",
    "┠─ATK─┐                   ┌──HP─┨",
    "┃  ~A~│                   │~H~  ┃",
    "┗━━━━━┷━━━━━━━━━━━━━━━━━━━┷━━━━━┛"};
const card_template_t HERO_BUTCHER_WINNER = {
    "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━WINNER━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
    "┃                                                                                                                                                                     ┃",
    "┃                                                     ███████╗ ██    ██╗ ████████╗ ██████╗  ██╗   ██╗ ███████╗ ██████╗                                                ┃",
    "┃                                                     ██   ██╝ ██    ██┃    ██ ╔━╝██╔════╝  ██║   ██┃ ██╔════╝ ██╔══██╗                                               ┃",
    "┃                                                     ███═██━╗ ██    ██┃    ██╔╝  ██║       ██╚██╗██┃ █████╗   ██████╔╝                                               ┃",
    "┃                                                     ██   ██┃ ██    ██┃    ██┃   ██║       ██   ║██┃ ██╔══╝   ██╔══██╗                                               ┃",
    "┃                                                     ███████┃ ╚██████╔╝    ██┃   ╚██████╗  ██╗  ╚██┃ ███████╗ ██║  ██║                                               ┃",
    "┃                                                     ╚━━━━━━╝  ╚━━━━━╝     ╚━╝    ╚═════╝  ╚━╝   ╚━╝ ╚══════╝ ╚═╝  ╚═╝                                               ┃",
    "┃                                                                                                                                                                     ┃",
    "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"};

const card_template_t HERO_SLARK_WINNER = {
    "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━WINNER━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
    "┃                                                                                   ╔════╗                                                                            ┃",
    "┃                                                               ███████╗  ██╗       ╚████╝   ██████╗  ██╗  ╔██╗                                                       ┃",
    "┃                                                               ██╔════╝  ██╝      ██    ██  ██╔══██╗ ██╝╔██ ╚╝                                                       ┃",
    "┃                                                               ███████╗  ██      ╔██═██═██╗ ██████╔╝ ████                                                            ┃",
    "┃                                                               ╚════██║ ╔██      ┃██    ██┃ ██╔══██╗ ██╗╚██                                                          ┃",
    "┃                                                               ███████║ ╚██████╗ ┃██    ██┃ ██║  ██║ ██┃  ╚██╗                                                       ┃",
    "┃                                                               ╚══════╝  ╚━━━━━╝ ╚━╝    ╚━╝ ╚═╝  ╚═╝ ╚━╝   ╚━╝                                                       ┃",
    "┃                                                                                                                                                                     ┃",
    "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"};
class Player;
class Ui
{
private:
    void displayMenuScreen(unsigned int &choicedMode);
    void selectCard(Player &player, unsigned int &choicedCard);
    void displayPlayerCard(Player &player, unsigned int &choicedCard);
    void displayCardList(std::vector<std::shared_ptr<Card>> &playerHandCard, int currentIndex);
    void displayBattle(std::vector<Player> &players, unsigned int playerId);
    void displayResult(Player &player);

public:
    enum UiState
    {
        INIT,
        CHOICE_CARD,
        WAIT_NEXT_TURN,
        WAIT_FOR_CONFIRM,
        UPDATE_BATTLE,
        RESULT
    };
    Ui();
    void updateUiOnState(UiState state, std::vector<Player> &players, unsigned int playerId, unsigned int &clone);

    ~Ui();
};

#endif // UI_H
