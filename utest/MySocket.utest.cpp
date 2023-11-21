#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MySocket/MySocket.h"
#include "mock/mock_MySocket.h"
class MySocketTest : public ::testing::Test {
protected:
    MySocket mySocket;
    Mock_MySocket mockSocket{mySocket};
    void SetUp() override {
        // Add any setup code that needs to be executed before each test
    }

    void TearDown() override {
        // Add any cleanup code that needs to be executed after each test
    }
};


// Example unit test for MySocket
TEST(MySocketTest, SendAndReceive) {
    // Create an instance of your mock
    Mock_MySocket mockSocket;

    // Set expectations on the mock
    std::vector<std::shared_ptr<Card>> hostHand = {std::make_shared<Card>(CardType::BRAWL)};
    std::vector<std::shared_ptr<Card>> clientHand = {std::make_shared<Card>(CardType::TECHIES)};

    EXPECT_CALL(mockSocket, sendInitCardPool(hostHand, clientHand))
        .Times(1);

    Player hostPlayer(PLAYER_1, nullptr);
    Player clientPlayer(PLAYER_2, nullptr);
    EXPECT_CALL(mockSocket, recvInitCardPool(testing::_, testing::_))
        .WillOnce([&hostPlayer, &clientPlayer](Player &host, Player &client) {
            host = hostPlayer;
            client = clientPlayer;
        });

    const int playerChoice = 42;
    EXPECT_CALL(mockSocket, sendPlayerChoice(playerChoice))
        .Times(1);

    EXPECT_CALL(mockSocket, receivePlayerChoice())
        .WillOnce(testing::Return(playerChoice));

    // Use the mock in your test
    mockSocket.sendInitCardPool(hostHand, clientHand);

    Player receivedHostPlayer(PLAYER_1, nullptr);
    Player receivedClientPlayer(PLAYER_2, nullptr);
    mockSocket.recvInitCardPool(receivedHostPlayer, receivedClientPlayer);

    mockSocket.sendPlayerChoice(playerChoice);
    int receivedChoice = mockSocket.receivePlayerChoice();

    // Assert your expectations
    EXPECT_EQ(receivedHostPlayer, hostPlayer);
    EXPECT_EQ(receivedClientPlayer, clientPlayer);
    EXPECT_EQ(receivedChoice, playerChoice);
}

// You can add more tests for other functionalities as needed.
