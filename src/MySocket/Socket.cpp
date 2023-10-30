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
#include "Entity/Minion.h"
MySocket::~MySocket()
{
    if (clientSocket_ != -1)
    {
        close(clientSocket_);
    }
}
void parseStringToVector(const std::string &input, std::vector<std::string> &output)
{
    std::istringstream ss(input);
    std::string line;
    while (std::getline(ss, line, '\n'))
    {
        output.push_back(line);
    }
}
std::string serializeVector(const std::vector<std::string> &vec)
{
    std::string serialized;
    for (const auto &item : vec)
    {
        serialized += item + '\n';
    }
    return serialized;
}
void MySocket::sendData(const std::string &serializedData)
{

    send(clientSocket_, serializedData.c_str(), serializedData.size(), 0);
}

int MySocket::receiveHandEntities(std::vector<std::string> &handEntities)
{
    ssize_t bytesReceived;
    char buffer[1024];
    bytesReceived = recv(clientSocket_, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0)
    {
        return -1; // Handle error or disconnection
    }

    std::string receivedString(buffer, bytesReceived);
    parseStringToVector(receivedString, handEntities);
    if (handEntities.size() > 0)
        return 0;
    return -1;
}

void MySocket::sendPlayerHandEntities(GameData_t &data)
{
    std::string serializedData;

    for (auto &entity : data.handEntities)
    {
        serializedData += entity->GetDescription() + '\n';
    }
    sendData(serializedData);
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

void MySocket::sendGameStats(const GameStats_t &player1Stats, const GameStats_t &player2Stats)
{
    std::string serializedData;

    // Serialize player1Stats
    serializedData += player1Stats.basicHeroStats + "+";
    serializedData += serializeVector(player1Stats.stats) + "+";
    serializedData += serializeVector(player1Stats.cardNames) + "+";
    serializedData += serializeVector(player1Stats.cardTypes) + "+";
    serializedData += serializeVector(player1Stats.cardSkills) + "+";
    serializedData += serializeVector(player1Stats.health) + "+";
    serializedData += serializeVector(player1Stats.attack) + "+";
    serializedData += serializeVector(player1Stats.activate) + "+";
    // Serialize player2Stats
    serializedData += player2Stats.basicHeroStats + "+";
    serializedData += serializeVector(player2Stats.stats) + "+";
    serializedData += serializeVector(player2Stats.cardNames) + "+";
    serializedData += serializeVector(player2Stats.cardTypes) + "+";
    serializedData += serializeVector(player2Stats.cardSkills) + "+";
    serializedData += serializeVector(player2Stats.health) + "+";
    serializedData += serializeVector(player2Stats.attack) + "+";
    serializedData += serializeVector(player2Stats.activate);

    sendData(serializedData);
}

int MySocket::receiveGameStats(GameStats_t &player1Stats, GameStats_t &player2Stats)
{
    char buffer[4056];
    ssize_t bytesReceived = recv(clientSocket_, buffer, sizeof(buffer), 0);

    if (bytesReceived < 0)
    {
        // Handle the error or connection termination
        return -1;
    }

    std::string receivedString(buffer, bytesReceived);

    std::vector<std::string> allData;
    size_t pos = 0;
    std::string token;
    while ((pos = receivedString.find('+')) != std::string::npos)
    {
        token = receivedString.substr(0, pos);
        allData.push_back(token);
        receivedString.erase(0, pos + 1);
    }
    std::cout << allData.size() << std::endl;
    if (allData.size() >= 7)
    {
        player1Stats.basicHeroStats = allData[0];
        parseStringToVector(allData[1], player1Stats.stats);
        parseStringToVector(allData[2], player1Stats.cardNames);
        parseStringToVector(allData[3], player1Stats.cardTypes);
        parseStringToVector(allData[4], player1Stats.cardSkills);
        parseStringToVector(allData[5], player1Stats.health);
        parseStringToVector(allData[6], player1Stats.attack);
        parseStringToVector(allData[7], player1Stats.activate);
    }

    if (allData.size() >= 15)
    {
        player2Stats.basicHeroStats = allData[8];
        parseStringToVector(allData[9], player2Stats.stats);
        parseStringToVector(allData[10], player2Stats.cardNames);
        parseStringToVector(allData[11], player2Stats.cardTypes);
        parseStringToVector(allData[12], player2Stats.cardSkills);
        parseStringToVector(allData[13], player2Stats.health);
        parseStringToVector(allData[14], player2Stats.attack);
        parseStringToVector(allData[15], player2Stats.activate);
    }

    return (allData.size() >= 16) ? 0 : -1;
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