#ifndef MOCK_MYSOCKET_H
#define MOCK_MYSOCKET_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MySocket/MySocket.h"

// Mock class for Mock_MySocket
class Mock_MySocket : public MySocket {
public:
    MOCK_METHOD(void, sendInitCardPool, (std::vector<std::shared_ptr<Card>> &hostPlayer, std::vector<std::shared_ptr<Card>> &clientPlayer));
    MOCK_METHOD(void, recvInitCardPool, (Player &hostPlayer, Player &clientPlayer));
    MOCK_METHOD(void, sendPlayerChoice, (int choice));
    MOCK_METHOD(int, receivePlayerChoice, ());
    MOCK_METHOD(void, initializeServer, ());
    MOCK_METHOD(void, initializeClient, ());
};
#endif // MOCK_MYSOCKET_H
