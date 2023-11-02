#include <iostream>
#include <vector>
#include <sstream>
typedef std::vector<std::string> card_template_t;
const card_template_t GAME_RULES =
    {
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

int main()
{

    for (auto &e : GAME_RULES)
    {
        std::cout << std::string(50, ' ') << e << std::endl;
    }
}
