#include <gtest/gtest.h>
#include "MySocket/MySocket.h"
#include "mock/mock.h"
#include <thread>

using ::testing::InSequence;
class MySocketTest : public ::testing::Test
{
protected:
    MockMySocket socketUnderTest{1}; // 1 for server mode
    std::thread serverThread;

    void SetUp() override
    {
        serverThread = std::thread([&]()
                                   {
                                       // Simulate server behavior
                                       std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some processing time
                                       std::cout << "Server is waiting for a client to connect..." << std::endl;
                                       // You can put the actual server logic here
                                   });
    }

    void TearDown() override
    {
        // Wait for the server thread to finish
        if (serverThread.joinable())
        {
            serverThread.join();
        }
    }
};

TEST_F(MySocketTest, SendAndReceiveInitCardPool)
{
    MockMySocket socketUnderTest{2};
}

TEST_F(MySocketTest, SendAndReceivePlayerChoice)
{
}