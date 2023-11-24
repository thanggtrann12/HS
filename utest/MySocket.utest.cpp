#define GTEST_FRIEND \
FRIEND_TEST(MySocketTest, InitializeServerSocket);
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MySocket/MySocket.h"
class Mock_MySocket : public MySocket {
public:
    // MOCK_METHOD(void, sendInitCardPool, (std::vector<std::shared_ptr<Card>> &hostPlayer, std::vector<std::shared_ptr<Card>> &clientPlayer));
    // MOCK_METHOD(void, recvInitCardPool, (Player &hostPlayer, Player &clientPlayer));
    // MOCK_METHOD(void, sendPlayerChoice, (int choice));
    // MOCK_METHOD(int, receivePlayerChoice, ());
    MOCK_METHOD(void, initializeServer, ());
    MOCK_METHOD(void, initializeClient, ());
};
class MySocketTest : public ::testing::Test
{
protected:

    Mock_MySocket mockSocket;
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(MySocketTest, InitializeServerSocket)
{
    MySocket mySocket(0);
    EXPECT_CALL(mockSocket, initializeServer());

    // // Add more specific assertions based on your requirements
    // ASSERT_TRUE(mySocket.serverSocket_ != -1);
}

