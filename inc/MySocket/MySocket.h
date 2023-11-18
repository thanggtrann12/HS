#ifndef MY_SOCKET_H
#define MY_SOCKET_H

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Helper/Helper.h"
#include "CardFactory/Card.h"
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
    void sendInitCardPool(const CardType *host, size_t hostSize, const CardType *client, size_t clientSize);
    void recvInitCardPool(CardType *&host, int &hostSize, CardType *&client, int &clientSize);
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
