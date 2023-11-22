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
    enum Mode
    {
        HOST = 1,
        CLIENT,
        SINGLE,
        UNKNOWN
    };
     MySocket() : mode_(UNKNOWN), clientSocket_(-1) {}
    bool registerSocketMode(Mode mode);
#if(mode_ == HOST)
    bool waitForClientConnect();
#endif
    ~MySocket();
    bool sendInitCardPool(Player &hostPlayer, Player &clientPlayer);
    bool recvInitCardPool(Player &hostPlayer, Player &clientPlayer);
    void sendPlayerChoice(int choice);
    int receivePlayerChoice();

private:
    Mode mode_;
    int serverSocket_;
    int clientSocket_;
    sockaddr_in serverAddress_;
    sockaddr_in clientAddress_;

    bool initializeServer();

    bool initializeClient();
};
#endif
