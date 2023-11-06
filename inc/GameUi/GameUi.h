#ifndef GAME_UI_H
#define GAME_UI_H
#include "Helper/Helper.h"
#include <iostream>
#include <string>
typedef std::vector<std::string> card_template_t;
const std::string EXTERNAL_BORDER_CHAR_UP_DOWN = "┃";
const std::string EXTERNAL_BORDER_CHAR_LEFT_RIGHT = "━";
const std::string EXTERNAL_BORDER_CHAR_TOP_LEFT = "╔";
const std::string EXTERNAL_BORDER_CHAR_TOP_RIGHT = "╗";
const std::string EXTERNAL_BORDER_CHAR_BOTTOM_LEFT = "╚";
const std::string EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT = "╝";

const char DELIMITER = '\v';

const card_template_t CARD_TEMPLATE_MINION_WITH_ABILITY = {
        "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
        "┃    ~NNNNNNNNNNNNNNNNNNNNN~    ┃",
        "┠───────────────┬───────────────┨",
        "┃ ~TTTTTTT~     │ ~SSSSSSSSS~   ┃",
        "┠───────────────┴───────────────┨",
        "┃   ~KKKKKKKKKKKKKKKKKKKKK      ┃",
        "┃   KKKKKKKKKKKKKKKKKKKKKKKKK   ┃",
        "┃              KKK~             ┃",
        "┠─ATK─┐                   ┌──HP─┨",
        "┃  ~A~│                   │~H~  ┃",
        "┗━━━━━┷━━━━━━━━━━━━━━━━━━━┷━━━━━┛"};

const card_template_t CARD_TEMPLATE_MINION_NO_ABILITY = {
        "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
        "┃    ~NNNNNNNNNNNNNNNNNNNNN~    ┃",
        "┠───────────────────────────────┨",
        "┃        ~TTTTTT~               ┃",
        "┠───────────────────────────────┨",
        "┃   ~KKKKKKKKKKKKKKKKKKKKKK     ┃",
        "┃   KKKKKKKKKKKKKKKKKKKKKKKKK   ┃",
        "┃              KKK~             ┃",
        "┠─ATK─┐                   ┌──HP─┨",
        "┃  ~A~│                   │~H~  ┃",
        "┗━━━━━┷━━━━━━━━━━━━━━━━━━━┷━━━━━┛"};
const card_template_t TOP_CENTRE_GRAPHIC = {
        "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
        "┃    ~MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM~     ┃",
        "┃                                                                                                                                                                           ┃",
        "┃                                                                                                                                                                           ┃"};

const card_template_t BOTTOM_CENTRE_GRAPHIC ={
        "┃                                                                                                                                                                           ┃",
        "┃                                                                                                                                                                           ┃",
        "┃    ~MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM      ┃",
        "┃    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM~     ┃",
        "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"};

const card_template_t GAME_RULES ={
        "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
        "┃                             The game have 2 players play turn by turn.                                                                                                    ┃",
        "┃                             There are 2 heroes in the game: Butcher and Slark                                                                                             ┃",
        "┃                                    - Butcher has 120 HP and 6 Attack.                                                                                                     ┃",
        "┃                                    - Slark has 72 HP and 10 Attack.                                                                                                       ┃",
        "┃                             There are 5 types of card                                                                                                                     ┃",
        "┃                                    - Ragnaros the Firelord - A minion with 1HP and 3 Attack.                                                                              ┃",
        "┃                                    - Bloodmage Thalnos - A minion with 1HP and 1 Attack.                                                                                  ┃",
        "┃                                    - Flametongue Totem - A shaman with 3HP and 0 Attack, but provides all alliance minions with a +1 Attack                               ┃",
        "┃                                    - Brawl - Destroy a random minion of the opposite player - Just use only 1 time.                                                       ┃",
        "┃                                    - Techies - A minion with 2HP and 1 Attack. On dead it deals 3 damage to both hero.                                                    ┃",
        "┃                                                                                                                                                                           ┃",
        "┃                             Enter the game, each player is random a hero and 10 cards from the board (player is able to hold card of the same type).                      ┃",
        "┃                             Each turn, a player can activate a card and place it into the battle. The card take effect immediately from that turn.                        ┃",
        "┃                             When an unit has 0 HP, it's removed from the battle, player lose that card.                                                                   ┃",
        "┃                             A hero only attack the other hero. Minion/shaman deals damage to all units.                                                                   ┃",
        "┃                             Player is defeated when his hero has 0 HP.                                                                                                    ┃",
        "┃                             When a turn finishes, player shall be able to see remaining HP and Attack of all units in the battle.                                         ┃",
        "┃                                                                                                                                                                           ┃",
        "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"};

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
class GameUi
{
public:
    GameUi();
    void GameUi_updateGameState(int playerIndex,int state, int &cardChoiced, const std::vector<GameData_t> &tableData);
    void GameUi_displayEntireTable(const std::vector<GameData_t> &tableData);
    void GameUi_displayGameRules();
    void GameUi_displayMenuOption(int &option);
    void GameUi_displayCardList(int &choice,const std::vector<std::shared_ptr<Minion>> &handEntities);
    void GameUi_waitForNextTurn();
    void GameUi_waitForConfirm();
    void GameUi_prepareConsole();
    void GameUi_displayResult(const std::vector<GameData_t> &tableData);
    ~GameUi(){};
    enum {
      INIT_STATE = 0,
      CHOICE_STATE,
      STATS_STATE,
      RESULT_STATE,
    };
private:
    void GameUi_displayCard(std::vector<std::vector<std::string>> &hand);
    void GameUi_replaceTextFromLeftSide(card_template_t &text, char flag, std::string new_text);
    void GameUi_replaceTextFromRightSide(card_template_t &text, char flag, std::string new_text);
    void GameUi_prepareForReplace(card_template_t &text);
    card_template_t GameUi_getTemplateWithText(card_template_t out, std::string name, int attack, int health, std::string skill, std::string status, std::string type);
    card_template_t GameUi_getCenterTemplateWithMessage(card_template_t out, std::vector<std::string> message);
};

#endif // GAME_UI_H