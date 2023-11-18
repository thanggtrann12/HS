#include <gtest/gtest.h>
#include "CardFactory/Card.h"
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
    MinionCard minionCard(CardType::FIRELORD);
    std::vector<std::shared_ptr<Card>> tableEntities;
    tableEntities.push_back(std::make_shared<MinionCard>(CardType::FIRELORD));
    gameData[1].tableEntities = tableEntities;
    ASSERT_EQ(gameData[1].tableEntities.size(), 1);
    ASSERT_EQ(gameData[1].tableEntities[0]->getCardType(), CardType::FIRELORD);
}

TEST_F(CardTest, BuffCard_playTest)
{
    // Create test data
    std::vector<GameData_t> gameData(2);
    BuffCard buffCard(CardType::SHAMAN);

    // Add cards to the table with varying types
    std::vector<std::shared_ptr<Card>> tableEntities;
    tableEntities.push_back(std::make_shared<MinionCard>(CardType::FIRELORD));
    tableEntities.push_back(std::make_shared<BuffCard>(CardType::SHAMAN));
    tableEntities.push_back(std::make_shared<MinionCard>(CardType::FIRELORD));
    gameData[0].tableEntities = tableEntities;
}

TEST_F(CardTest, SpellCard_playTest)
{
    // Create test data
    std::vector<GameData_t> gameData(2);
    SpellCard spellCard(CardType::BRAWL);

    // Add cards to the table with varying types
    std::vector<std::shared_ptr<Card>> tableEntities;
    tableEntities.push_back(std::make_shared<MinionCard>(CardType::FIRELORD));
    tableEntities.push_back(std::make_shared<BuffCard>(CardType::SHAMAN));
    tableEntities.push_back(std::make_shared<MinionCard>(CardType::FIRELORD));
    gameData[1].tableEntities = tableEntities;
}
