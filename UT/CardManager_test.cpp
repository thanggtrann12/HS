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

TEST_F(CardManagerTest, CardManager_getCardFromPocketTest) {
    std::vector<std::shared_ptr<Card>> playerHand;
    cardManager.CardManager_getCardFromPocket(playerHand);

    // Assuming getCardFromPocket adds 10 cards to playerHand
    ASSERT_EQ(playerHand.size(), 10);
}

TEST_F(CardManagerTest, CardManager_assignHeroToPlayerTest) {
    unsigned int heroNum = 0;
    auto assignedHero = cardManager.CardManager_assignHeroToPlayer(heroNum);

    // Assuming assignHeroToPlayer returns a valid shared_ptr<Hero>
    ASSERT_NE(assignedHero, nullptr);
}

TEST_F(CardManagerTest, CardManager_drawRandomCardTest) {
    auto drawnCard = cardManager.CardManager_drawRandomCard();

    // Assuming drawRandomCard returns a valid shared_ptr<Card>
    ASSERT_NE(drawnCard, nullptr);
}

TEST_F(CardManagerTest, CardManager_pushCardToTableTest) {
    std::vector<std::shared_ptr<Card>> playerTable;

    // Assuming pushCardToTable adds a card to playerTable
    cardManager.CardManager_pushCardToTable(playerTable, Card::CardType::FIRELORD);

    ASSERT_EQ(playerTable.size(), 1);
    ASSERT_EQ(playerTable[0]->getCardType(), Card::CardType::FIRELORD);
}
