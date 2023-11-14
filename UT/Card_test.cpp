#include <gtest/gtest.h>
#include "CardManager/CardFactory/Card.h"
#include "CardManager/Hero.h"
#include "Helper/Helper.h"
#include <gtest/gtest.h>
class CardTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // You can add common setup code here if needed
    }

    void TearDown() override
    {
        // You can add common teardown code here if needed
    }
};

TEST_F(CardTest, MinionCard_playTest)
{
    // Create test data
    std::vector<GameData_t> gameData(2);
    MinionCard minionCard("MinionCardTest", 10, 5, Card::CardType::FIRELORD);
    std::vector<std::shared_ptr<Card>> tableEntities;
    tableEntities.push_back(std::make_shared<MinionCard>("DefenderMinion", 10, 5, Card::CardType::FIRELORD));
    gameData[1].tableEntities = tableEntities;
    ASSERT_EQ(gameData[1].tableEntities.size(), 1);
    ASSERT_EQ(gameData[1].tableEntities[0]->getCardType(), Card::CardType::FIRELORD);
}

TEST_F(CardTest, BuffCard_playTest)
{
    // Create test data
    std::vector<GameData_t> gameData(2);
    BuffCard buffCard("BuffCardTest", 0, 0, "BuffSkill", Card::CardType::SHAMAN);

    // Add cards to the table with varying types
    std::vector<std::shared_ptr<Card>> tableEntities;
    tableEntities.push_back(std::make_shared<MinionCard>("Minion1", 10, 5, Card::CardType::FIRELORD));
    tableEntities.push_back(std::make_shared<BuffCard>("BuffCard1", 5, 2, "BuffSkill", Card::CardType::SHAMAN));
    tableEntities.push_back(std::make_shared<MinionCard>("Minion2", 8, 4, Card::CardType::FIRELORD));
    gameData[0].tableEntities = tableEntities;
}

TEST_F(CardTest, SpellCard_playTest)
{
    // Create test data
    std::vector<GameData_t> gameData(2);
    SpellCard spellCard("SpellCardTest", "SpellSkill", Card::CardType::BRAWL);

    // Add cards to the table with varying types
    std::vector<std::shared_ptr<Card>> tableEntities;
    tableEntities.push_back(std::make_shared<MinionCard>("Minion1", 10, 5, Card::CardType::FIRELORD));
    tableEntities.push_back(std::make_shared<BuffCard>("BuffCard1", 5, 2, "BuffSkill", Card::CardType::SHAMAN));
    tableEntities.push_back(std::make_shared<MinionCard>("Minion2", 8, 4, Card::CardType::FIRELORD));
    gameData[1].tableEntities = tableEntities;
}
