#include "Entity/Minion.h"
#include <iostream>
void FlametongueTotem::applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex)
{
  if (!player[playerIndex].tableEntities.empty())
  {
    player[playerIndex].stats.push_back("Card buffed: ");
    auto &playedCard = player[playerIndex].handEntities[entitiesIndex];
    for (auto &minion : player[playerIndex].tableEntities)
    {
      if (minion->GetEntitiesType() != EntityType::SHAMAN && !playedCard->IsApply())
      {
        minion->SetAttack(shamanbuff);
        playedCard->Applied();
        player[playerIndex].stats.push_back(minion->GetDescription());
      }
    }
  }
}

void RagnarosTheFirelord::applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex)
{
  uint8_t currentPlayer = playerIndex;
  uint8_t oppenentPlayer = 1 - playerIndex;
  auto &playedCard = player[currentPlayer].handEntities[entitiesIndex];
  if (player[oppenentPlayer].tableEntities.size() > 0)
  {
    player[oppenentPlayer].stats.push_back("Card eliminated: ");
    for (auto &minion : player[oppenentPlayer].tableEntities)
    {
      minion->TakeDamage(playedCard->GetAttack());
      if (!minion->IsAlive())
      {
        if (minion->GetEntitiesType() == EntityType::TECHIES)
        {
          Techies techiesInstance;
          techiesInstance.applyEffect(player, entitiesIndex, playerIndex);
        }
        if (minion->GetEntitiesType() == EntityType::SHAMAN)
        {
          shamanCnt++;
        }
        player[oppenentPlayer].stats.push_back("- " + minion->GetName());
      }
    }
    for (auto &minion : player[oppenentPlayer].tableEntities)
    {
      if (minion->IsAlive())
      {
        minion->SetAttack(-shamanCnt);
      }
    }
  }
}

void BloodmageThalnos::applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex)
{
  uint8_t currentPlayer = playerIndex;
  uint8_t oppenentPlayer = 1 - playerIndex;
  auto &playedCard = player[currentPlayer].handEntities[entitiesIndex];
  if (player[oppenentPlayer].tableEntities.size() > 0)
  {
    player[oppenentPlayer].stats.push_back("Card eliminated: ");
    for (auto &minion : player[oppenentPlayer].tableEntities)
    {
      minion->TakeDamage(playedCard->GetAttack());
      if (!minion->IsAlive())
      {
        if (minion->GetEntitiesType() == EntityType::TECHIES)
        {
          Techies techiesInstance;
          techiesInstance.applyEffect(player, entitiesIndex, playerIndex);
        }
        if (minion->GetEntitiesType() == EntityType::SHAMAN)
        {
          shamanCnt++;
        }
        player[oppenentPlayer].stats.push_back("- " + minion->GetName());
      }
    }
    for (auto &minion : player[oppenentPlayer].tableEntities)
    {
      if (minion->IsAlive())
      {
        minion->SetAttack(-shamanCnt);
      }
    }
  }
}

void Brawl::applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex)
{
  uint8_t currentPlayer = playerIndex;
  uint8_t oppenentPlayer = 1 - playerIndex;
  auto &opponentPlayerEntities = player[oppenentPlayer].tableEntities;
  if (opponentPlayerEntities.size() > 0)
  {
    int randomIndex = rand() % opponentPlayerEntities.size();
    player[oppenentPlayer].stats.push_back(player[oppenentPlayer].tableEntities[randomIndex]->GetName() + " have been eleminated");
    opponentPlayerEntities.erase(opponentPlayerEntities.begin() + randomIndex);
    if (opponentPlayerEntities[randomIndex]->GetEntitiesType() == EntityType::TECHIES)
    {
      player[oppenentPlayer].stats.push_back("Techies have been eleminated");
      Techies techiesInstance;
      techiesInstance.applyEffect(player, entitiesIndex, playerIndex);
    }
  }
}

void Techies::applyEffect(std::vector<GameData_t> player, uint8_t entitiesIndex, uint8_t playerIndex)
{
  UNUSED(entitiesIndex);
  uint8_t currentPlayer = playerIndex;
  uint8_t oppenentPlayer = 1 - playerIndex;
  player[currentPlayer].hero->AttackHero(player[oppenentPlayer].hero, player[currentPlayer].hero->GetAttack());
  player[currentPlayer].stats.push_back(player[currentPlayer].hero->GetName() + " get 3 damage on Techies eleminated");
  player[oppenentPlayer].hero->AttackHero(player[currentPlayer].hero, player[oppenentPlayer].hero->GetAttack());
  player[oppenentPlayer].stats.push_back(player[oppenentPlayer].hero->GetName() + " get 3 damage on Techies eleminated");
}