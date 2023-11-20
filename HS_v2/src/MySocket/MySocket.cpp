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

MySocket::~MySocket()
{
    if (clientSocket_ != -1)
    {
        close(clientSocket_);
    }
}

void MySocket::sendInitCardPool(std::vector<std::shared_ptr<Card>> &hostPlayer, std::vector<std::shared_ptr<Card>> &clientPlayer)
{
    size_t hostHandSize = hostPlayer.size();
    size_t clientHandSize = clientPlayer.size();
    size_t combined_length = hostHandSize + clientHandSize + 1;
    CardType *combined_array = new CardType[combined_length];

    // Set the size of the host player's hand
    combined_array[0] = static_cast<CardType>(hostHandSize);

    // Fill in host player's card types
    for (size_t i = 0; i < hostHandSize; ++i)
    {
        combined_array[i + 1] = hostPlayer[i]->getCardType();
        // std::cout << static_cast<int>(hostPlayer[i]->getCardType()) << std::endl;
    }

    // Fill in client player's card types
    for (size_t i = 0; i < clientHandSize; ++i)
    {
        combined_array[i + hostHandSize + 1] = clientPlayer[i]->getCardType();
        // std::cout << static_cast<int>(clientPlayer[i]->getCardType()) << std::endl;
    }

    // Send the entire array
    send(clientSocket_, combined_array, combined_length * sizeof(CardType), 0);

    // Don't forget to free the dynamically allocated array
    delete[] combined_array;
}

void MySocket::recvInitCardPool(Player &hostPlayer, Player &clientPlayer)
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

    // std::cout << "hostHandSize: " << hostHandSize << std::endl;
    // std::cout << "arrayLength: " << arrayLength << std::endl;

    // Update host player cards
    for (size_t i = 1; i <= hostHandSize; i++)
    {
        hostPlayer.updateCard(receiveArr[i]);
        // std::cout << static_cast<int>(receiveArr[i]) << std::endl;
    }

    // Update client player cards
    for (size_t i = hostHandSize + 1; i < arrayLength; i++)
    {
        clientPlayer.updateCard(receiveArr[i]);
        // std::cout << static_cast<int>(receiveArr[i]) << std::endl;
    }
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

void MySocket::initializeServer()
{
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(8082);
    serverAddress_.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket_, (struct sockaddr *)&serverAddress_, sizeof(serverAddress_)) == -1)
    {
        std::cerr << "Error binding socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket_, 5) == -1)
    {
        std::cerr << "Error listening on socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is waiting for a client to connect..." << std::endl;

    clientSocket_ = accept(serverSocket_, NULL, NULL);
    if (clientSocket_ == -1)
    {
        std::cerr << "Error accepting client connection." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void MySocket::initializeClient()
{
    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket_ == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(8082);
    serverAddress_.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket_, (struct sockaddr *)&serverAddress_, sizeof(serverAddress_)) == -1)
    {
        std::cerr << "Error connecting to the server." << std::endl;
        exit(EXIT_FAILURE);
    }
}