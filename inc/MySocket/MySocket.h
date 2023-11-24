#ifndef MY_SOCKET_H
#define MY_SOCKET_H
#include "Player/Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8081

class MySocket
{
public:
    MySocket(int mode) : mode_(mode), clientSocket_(-1)
    {
        if (mode_ == 1)
        {
            initializeServer();
        }
        else if (mode_ == 2)
        {
            initializeClient();
        }
    }

    ~MySocket();
    void sendInitCardPool(std::vector<std::shared_ptr<Card>> &hostPlayer, std::vector<std::shared_ptr<Card>> &clientPlayer);
    void recvInitCardPool(Player &hostPlayer, Player &clientPlayer);
    void sendPlayerChoice(int choice);
    int receivePlayerChoice();

private:
#ifdef GTEST_FRIEND
  GTEST_FRIEND
#endif
    int mode_;
    int serverSocket_;
    int clientSocket_;
    sockaddr_in serverAddress_;
    sockaddr_in clientAddress_;

    void initializeServer();

    void initializeClient();
};
#endif
