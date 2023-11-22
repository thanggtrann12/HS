#ifndef MOCK_MYSOCKET_H
#define MOCK_MYSOCKET_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MySocket/MySocket.h"

// Mock class for Mock_MySocket
class Mock_MySocket : public MySocket {
public:
    MOCK_METHOD(bool, registerSocketMode, (Mode mode));
    MOCK_METHOD(bool, waitForClientConnect, ());
    MOCK_METHOD(bool, sendInitCardPool, (Player &hostPlayer, Player &clientPlayer));
    MOCK_METHOD(bool, recvInitCardPool, (Player &hostPlayer, Player &clientPlayer));
    MOCK_METHOD(void, sendPlayerChoice, (int choice));
    MOCK_METHOD(int, receivePlayerChoice, ());
    MOCK_METHOD(bool, initializeServer, ());
    MOCK_METHOD(bool, initializeClient, ());
};
#endif // MOCK_MYSOCKET_H
