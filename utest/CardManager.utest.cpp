#include "gtest/gtest.h"
#include "CardManager/CardManager.h"
#include "Card/CardFactory.h"
#include "Player/Player.h"
#include "Card/Card.h"
#include <vector>

class CardManagerTest : public ::testing::Test {
protected:
  CardManager *cardManager =  new CardManager();
  Player *attacker;
  Player *defender;

  virtual void SetUp() {
    attacker = new Player(PlayerId::PLAYER_1, nullptr);
    attacker->setHero(BUTCHER);
    defender = new Player(PlayerId::PLAYER_2, nullptr);
    defender->setHero(SLARK);
  }
};

TEST_F(CardManagerTest, GetCardFromPocket) {
  std::shared_ptr<Card> card = cardManager->getCardFromPocket();
  ASSERT_TRUE(card != nullptr);
}

// Test case for generateCardFromCardType() method
TEST_F(CardManagerTest, GenerateCardFromCardType) {

  cardManager->generateCardFromCardType(attacker->getHand(), CardType::FIRELORD);
  ASSERT_EQ(1, attacker->getHand().size());
  ASSERT_EQ(CardType::FIRELORD, attacker->getHand()[0]->getCardType());
  cardManager->generateCardFromCardType(attacker->getHand(), CardType::THALNOS);
  ASSERT_EQ(2, attacker->getHand().size());
  ASSERT_EQ(CardType::THALNOS, attacker->getHand()[1]->getCardType());
  cardManager->generateCardFromCardType(attacker->getHand(), CardType::SHAMAN);
  ASSERT_EQ(3, attacker->getHand().size());
  ASSERT_EQ(CardType::SHAMAN, attacker->getHand()[2]->getCardType());
  cardManager->generateCardFromCardType(attacker->getHand(), CardType::TECHIES);
  ASSERT_EQ(4, attacker->getHand().size());
  ASSERT_EQ(CardType::TECHIES, attacker->getHand()[3]->getCardType());
  cardManager->generateCardFromCardType(attacker->getHand(), CardType::BRAWL);
  ASSERT_EQ(5, attacker->getHand().size());
  ASSERT_EQ(CardType::BRAWL, attacker->getHand()[4]->getCardType());
}

TEST_F(CardManagerTest, ActiveCard)
{
    attacker->getHand().clear();
    // Test scenario 1: card type is not BRAWL
    cardManager->generateCardFromCardType(attacker->getHand(), CardType::FIRELORD);
    std::vector<std::shared_ptr<Card>>::iterator cardPlayed = attacker->getHand().begin();
    cardManager->activeCard(*attacker, *defender, cardPlayed);
    ASSERT_EQ(attacker->getHand().size(), 0);
    ASSERT_EQ(attacker->getBattle().size(), 1);

    EXPECT_NE((*cardPlayed)->getCardType(), CardType::BRAWL);
    // Test scenario 2: card type is BRAWL
    attacker->getHand().clear();
    cardManager->generateCardFromCardType(attacker->getHand(), CardType::BRAWL);
    cardPlayed = attacker->getHand().begin();
    cardManager->activeCard(*attacker, *defender, cardPlayed);
    ASSERT_EQ(attacker->getHand().size(), 0);

}