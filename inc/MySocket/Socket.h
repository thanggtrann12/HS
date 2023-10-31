#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Helper/Helper.h"
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
    void sendPlayerHandEntities(GameData_t &data);
    int receiveHandEntities(std::vector<std::string> &handEntities);
    void sendData(const std::string &serializedData);
    void sendPlayerChoice(int choice);
    int receivePlayerChoice();
    void sendGameStats(const GameStats_t &player1Stats, const GameStats_t &player2Stats);
    int receiveGameStats(GameStats_t &player1Stats, GameStats_t &player2Stats);

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
