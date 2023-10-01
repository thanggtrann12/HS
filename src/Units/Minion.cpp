#include "Units/Minion.h"

FlametongueTotem::FlametongueTotem()
    : Minion("Flametongue Totem", 3, 0, CardType::SPELL) {}

void FlametongueTotem::applyBuff(std::vector<std::shared_ptr<Minion>> &minions)
{
    for (auto &minion : minions)
    {
        if (minion->getCardType() != CardType::SPELL)
            minion->boostAttack(1);
    }
}
RagnarosTheFirelord::RagnarosTheFirelord()
    : Minion("Ragnaros the Firelord", 1, 3, CardType::MINION) {}
BloodmageThalnos::BloodmageThalnos()
    : Minion("Bloodmage Thalnos", 1, 1, CardType::MINION) {}
Brawl::Brawl()
    : Minion("Brawl", 0, 0, CardType::BRAWL){};
Techies::Techies()
    : Minion("Techies", 2, 1, CardType::TECHIES) {}