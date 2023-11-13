#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Helper/Helper.h"
#include "CardManager/CardFactory/Card.h"
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
    void sendInitCardPool(const Card::CardType *host, size_t hostSize, const Card::CardType *client, size_t clientSize);
    void recvInitCardPool(Card::CardType *&host, int &hostSize, Card::CardType *&client, int &clientSize);
    void sendPlayerChoice(int choice);
    int receivePlayerChoice();

private:
    int mode_;
    int serverSocket_;
    int clientSocket_;
    sockaddr_in serverAddress_;
    sockaddr_in clientAddress_;

    void initializeServer();

    void initializeClient();
};
#endif
