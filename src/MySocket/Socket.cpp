#include "MySocket/Socket.h"
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

void MySocket::sendInitCardPool(const Card::CardType *host, size_t hostSize, const Card::CardType *client, size_t clientSize)
{

    size_t combined_length = hostSize + clientSize + 2;
    Card::CardType *combined_array = new Card::CardType[combined_length];
    size_t total_size_bytes = sizeof(Card::CardType) * (hostSize + clientSize + 2);
    combined_array[0] = static_cast<Card::CardType>(hostSize);
    combined_array[1] = static_cast<Card::CardType>(clientSize);
    for (size_t i = 0; i < hostSize; ++i)
    {
        combined_array[i + 2] = host[i];
    }
    for (size_t i = 0; i < clientSize; ++i)
    {
        combined_array[i + hostSize + 2] = client[i];
    }
    send(clientSocket_, combined_array, total_size_bytes, 0);
}

void MySocket::recvInitCardPool(Card::CardType *&host, int &hostSize, Card::CardType *&client, int &clientSize)
{
    char buffer[4056];
    ssize_t total_size_bytes = recv(clientSocket_, buffer, sizeof(buffer), 0);

    // Assuming Card::CardType is an enum
    Card::CardType *combined_array = reinterpret_cast<Card::CardType *>(buffer);

    // Extract the lengths of the original arrays
    hostSize = static_cast<size_t>(combined_array[0]);
    clientSize = static_cast<size_t>(combined_array[1]);

    // Allocate memory for host and client arrays
    host = new Card::CardType[hostSize];
    client = new Card::CardType[clientSize];

    for (int i = 0; i < hostSize; ++i)
    {
        host[i] = combined_array[i + 2];
    }

    for (int i = 0; i < clientSize; ++i)
    {
        client[i] = combined_array[i + hostSize + 2];
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
    std::cout << "Client connected" << std::endl;
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