#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mock/mock_Hero.h"

// Test fixture for Mock_Hero
class MockHeroTest : public ::testing::Test {
protected:
    Mock_Hero mockHero;
};

// Test case for initialization
TEST_F(MockHeroTest, InitHero) {
    EXPECT_CALL(mockHero, initHero()).Times(1);

    mockHero.initHero();
}

// Test case for checking if the hero is alive
TEST_F(MockHeroTest, IsAlive) {
    EXPECT_CALL(mockHero, IsAlive()).WillOnce(::testing::Return(true));

    bool alive = mockHero.IsAlive();
    ASSERT_TRUE(alive);
}

// Test case for taking damage
TEST_F(MockHeroTest, TakeDamage) {
    unsigned int damage = 10;
    EXPECT_CALL(mockHero, takeDamage(damage)).Times(1);
    mockHero.takeDamage(damage);
}

// Test case for getting hero description
TEST_F(MockHeroTest, GetDescription) {
    // Set up a description for the hero
    std::string expectedDescription = "Mock Hero Description";
    ON_CALL(mockHero, getDescription()).WillByDefault(::testing::Return(expectedDescription));

    std::string description = mockHero.getDescription();
    ASSERT_EQ(description, expectedDescription);
}

// Add more test cases as needed
