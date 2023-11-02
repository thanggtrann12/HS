#include "Entity/Minion.h"
#include "Entity/Hero.h"
#include <iostream>
#include <algorithm>
#include "Helper/Helper.h"
void Minion::DameToAllEntities(GameData_t &player, int damage)
{
    std::vector<size_t> indicesToRemove;
    for (size_t i = 0; i < player.tableEntities.size(); ++i)
    {
        auto &entity = player.tableEntities[i];
        entity->TakeDamage(damage);
        if (!entity->IsAlive())
        {
            indicesToRemove.push_back(i);
            player.stats.push_back("Card " + entity->GetDescription() + " removed");
        }
    }

    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it)
    {
        player.tableEntities.erase(player.tableEntities.begin() + *it);
    }

    player.hero->TakeDamage(damage);
}
void FlametongueTotem::applyEffect(std::vector<GameData_t> &player, int playerIndex)
{
    if (!player[playerIndex].tableEntities.empty())
    {
        player[playerIndex].stats.push_back("Card buffed: ");
        for (auto &minion : player[playerIndex].tableEntities)
        {
            if (minion->GetEntitiesType() != EntityType::SHAMAN && minion->GetEntitiesType() != EntityType::BRAWL)
            {
                minion->SetAttack(shamanbuff);
                player[playerIndex].stats.push_back("  -" + minion->GetDescription());
            }
        }
    }
}

void RagnarosTheFirelord::applyEffect(std::vector<GameData_t> &player, int playerIndex)
{
    Techies techiesInstance;
    techiesInstance.applyEffect(player, playerIndex);
}

void BloodmageThalnos::applyEffect(std::vector<GameData_t> &player, int playerIndex)
{
    Techies techiesInstance;
    techiesInstance.applyEffect(player, playerIndex);
}

void Brawl::applyEffect(std::vector<GameData_t> &player, int playerIndex)
{
    int currentPlayer = playerIndex;
    int opponentPlayer = 1 - playerIndex;
    auto &opponentPlayerEntities = player[opponentPlayer].tableEntities;

    if (!opponentPlayerEntities.empty())
    {
        int randomIndex = rand() % opponentPlayerEntities.size();

        if (randomIndex >= 0 && randomIndex < opponentPlayerEntities.size())
        {
            auto &eliminatedEntity = opponentPlayerEntities[randomIndex];

            player[opponentPlayer].stats.push_back(player[opponentPlayer].hero->GetName() + "'s " + eliminatedEntity->GetName() + " have been eliminated");

            if (eliminatedEntity->GetEntitiesType() == EntityType::TECHIES)
            {
                player[opponentPlayer].stats.push_back("Techies have been eliminated");

                if (currentPlayer < player.size() && opponentPlayer < player.size())
                {
                    player[currentPlayer].hero->AttackHero(player[opponentPlayer].hero, player[currentPlayer].hero->GetAttack());
                    player[currentPlayer].stats.push_back(player[currentPlayer].hero->GetName() + " gets 3 damage on Techies eliminated");
                    player[opponentPlayer].hero->AttackHero(player[currentPlayer].hero, player[opponentPlayer].hero->GetAttack());
                    player[opponentPlayer].stats.push_back(player[opponentPlayer].hero->GetName() + " gets 3 damage on Techies eliminated");
                }
            }

            if (randomIndex >= 0 && randomIndex < opponentPlayerEntities.size())
            {
                opponentPlayerEntities.erase(opponentPlayerEntities.begin() + randomIndex);
            }
        }
    }
}

void Techies::applyEffect(std::vector<GameData_t> &player, int playerIndex)
{
    for (auto entity : player[playerIndex].tableEntities)
    {
        if (entity->GetEntitiesType() == EntityType::TECHIES && !entity->IsAlive())
        {
            player[playerIndex].hero->TakeDamage(3);
            player[1 - playerIndex].hero->TakeDamage(3);
            player[playerIndex].stats.push_back(player[playerIndex].hero->GetName() + " gets 3 damage on Techies eliminated");
            player[1 - playerIndex].stats.push_back(player[1 - playerIndex].hero->GetName() + " gets 3 damage on Techies eliminated");
        }
    }
}