#include "MySocket/MySocket.h"
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <iomanip>

bool MySocket::registerSocketMode(Mode mode)
{
    mode_ = mode;
    if (mode_ == HOST)
    {
        return initializeServer();
    }
    else if (mode_ == CLIENT)
    {
        return initializeClient();
    }
    return false;
}
#if (mode_ == HOST)
bool MySocket::waitForClientConnect()
{
    clientSocket_ = accept(serverSocket_, NULL, NULL);
    if (clientSocket_ == -1)
        return false;
    return true;
}
#endif

MySocket::~MySocket()
{
    if (clientSocket_ != -1)
    {
        close(clientSocket_);
    }
}

bool MySocket::sendInitCardPool(Player &hostPlayer, Player &clientPlayer)
{
    size_t hostHandSize = hostPlayer.getHand().size();
    size_t clientHandSize = clientPlayer.getHand().size();
    size_t combined_length = hostHandSize + clientHandSize + 1;
    CardType *combined_array = new CardType[combined_length];

    // Set the size of the host player's hand
    combined_array[0] = static_cast<CardType>(hostHandSize);

    // Fill in host player's card types
    for (size_t i = 0; i < hostHandSize; ++i)
    {
        combined_array[i + 1] = hostPlayer.getHand()[i]->getCardType();
    }

    // Fill in client player's card types
    for (size_t i = 0; i < clientHandSize; ++i)
    {
        combined_array[i + hostHandSize + 1] = clientPlayer.getHand()[i]->getCardType();
    }

    if (send(clientSocket_, combined_array, combined_length * sizeof(CardType), 0) != -1)
    {
        delete[] combined_array;
        return true;
    }
    return false;
}

bool MySocket::recvInitCardPool(Player &hostPlayer, Player &clientPlayer)
{
    auto &hostPlayerHand = hostPlayer.getHand();
    auto &clientPlayerHand = clientPlayer.getHand();
    hostPlayerHand.clear();
    clientPlayerHand.clear();

    char buffer[4056];
    ssize_t total_size_bytes = recv(clientSocket_, buffer, sizeof(buffer), 0);

    // Cast the received buffer to the CardType array
    CardType *receiveArr = reinterpret_cast<CardType *>(buffer);
    size_t arrayLength = total_size_bytes / sizeof(CardType);
    size_t hostHandSize = static_cast<size_t>(receiveArr[0]);
    if (arrayLength > 0)
    {
        for (size_t i = 1; i <= hostHandSize; i++)
        {
            hostPlayer.updateCard(receiveArr[i]);
        }
        for (size_t i = hostHandSize + 1; i < arrayLength; i++)
        {
            clientPlayer.updateCard(receiveArr[i]);
        }
        return true;
    }
    return false;
}

void MySocket::sendPlayerChoice(int choice)
{
    send(clientSocket_, &choice, sizeof(int), 0);
}

int MySocket::receivePlayerChoice()
{
    int receivedInt;
    if (recv(clientSocket_, &receivedInt, sizeof(int), 0) == -1)
    {
        std::cerr << "Error receiving data" << std::endl;
        return -1;
    }
    return receivedInt;
}

bool MySocket::initializeServer()
{
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1)
        return false;

    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(8082);
    serverAddress_.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket_, (struct sockaddr *)&serverAddress_, sizeof(serverAddress_)) == -1)
        return false;

    if (listen(serverSocket_, 5) == -1)
        return false;
    return true;
}

bool MySocket::initializeClient()
{
    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket_ == -1)
        return false;

    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(8082);
    serverAddress_.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(clientSocket_, (struct sockaddr *)&serverAddress_, sizeof(serverAddress_)) == -1)
        return false;
    return true;
}