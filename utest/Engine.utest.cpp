#include <gtest/gtest.h>
#include "Engine/Engine.h"

TEST(EngineTest, EndTurn_ValidInput_ValidOutput)
{
    // Arrange
    Engine engine;

    // Act
    engine.endTurn();

    // Assert
    EXPECT_EQ(engine.currentTurn, engine.nextTurn);
}

TEST(EngineTest, EndTurn_InvalidInput_ValidOutput)
{
    // Arrange
    Engine engine;

    // Act
    engine.currentTurn = 1;
    engine.nextTurn = 2;
    engine.endTurn();

    // Assert
    EXPECT_EQ(engine.currentTurn, 2);
    EXPECT_EQ(engine.nextTurn, 1);
}