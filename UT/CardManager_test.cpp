#include <gtest/gtest.h>
#include "CardManager/CardManager.h"

class CardManagerTest : public ::testing::Test {
protected:
    CardManager cardManager;

    void SetUp() override {
        // You can add common setup code here if needed
    }

    void TearDown() override {
        // You can add common teardown code here if needed
    }
};

TEST_F(CardManagerTest, getCardFromPocketTest) {
    std::vector<std::shared_ptr<Card>> playerHand;
    cardManager.getCardFromPocket(playerHand);

    // Assuming getCardFromPocket adds 10 cards to playerHand
    ASSERT_EQ(playerHand.size(), 10);
}

TEST_F(CardManagerTest, assignHeroToPlayerTest) {
    unsigned int heroNum = 0;
    auto assignedHero = cardManager.assignHeroToPlayer(heroNum);

    // Assuming assignHeroToPlayer returns a valid shared_ptr<Hero>
    ASSERT_NE(assignedHero, nullptr);
}

TEST_F(CardManagerTest, drawRandomCardTest) {
    auto drawnCard = cardManager.drawRandomCard();

    // Assuming drawRandomCard returns a valid shared_ptr<Card>
    ASSERT_NE(drawnCard, nullptr);
}

TEST_F(CardManagerTest, pushCardToTableTest) {
    std::vector<std::shared_ptr<Card>> playerTable;

    // Assuming pushCardToTable adds a card to playerTable
    cardManager.pushCardToTable(playerTable, CardType::FIRELORD);

    ASSERT_EQ(playerTable.size(), 1);
    ASSERT_EQ(playerTable[0]->getCardType(), CardType::FIRELORD);
}
