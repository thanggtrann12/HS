#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
struct data_t
{
    int mode;
    int choice;
    std::vector<std::string> clientHandCards;
    std::vector<std::string> clientHeroStats;
    std::vector<std::string> serverHeroStats;
    std::vector<std::string> gameInfos;
};
enum
{
    HAND_CARD = 0,
    PLAY_CARD,
    BATTTLE_STATS,
    RESULT
};
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
    void sendData(data_t &sendData);
    int receiveData(data_t &receivedData);
    // void sendData(const std::string &data);

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
