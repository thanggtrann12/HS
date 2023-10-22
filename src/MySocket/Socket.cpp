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

void MySocket::sendData(data_t &sendData)
{
    std::string serializedData = std::to_string(sendData.mode) + ":" +
                                 std::to_string(sendData.choice) + ":";
    for (const std::string &option : sendData.clientHandCards)
    {
        serializedData += option + '\n';
    }
    serializedData += ":";
    for (const std::string &option : sendData.clientHeroStats)
    {
        serializedData += option + '\n';
    }
    serializedData += ":";
    for (const std::string &option : sendData.serverHeroStats)
    {
        serializedData += option + '\n';
    }
    serializedData += ":";
    for (const std::string &option : sendData.gameInfos)
    {
        serializedData += option + '\n';
    }
    send(clientSocket_, serializedData.c_str(), serializedData.size(), 0);
}
void parseStringToVector(const std::string &input, std::vector<std::string> &output)
{
    std::istringstream ss(input);
    std::string line;
    while (std::getline(ss, line, '\n'))
    {
        output.push_back(line);
        std::cout << line << std::endl;
    }
}

int MySocket::receiveData(data_t &receivedData)
{
    ssize_t bytesReceived;
    char buffer[1024];

    bytesReceived = recv(clientSocket_, buffer, sizeof(buffer), 0);
    std::string receivedString(buffer, bytesReceived);
    size_t delimiterPos1 = receivedString.find(':');
    size_t delimiterPos2 = receivedString.find(':', delimiterPos1 + 1);
    size_t delimiterPos3 = receivedString.find(':', delimiterPos2 + 1);
    size_t delimiterPos4 = receivedString.find(':', delimiterPos3 + 1);
    size_t delimiterPos5 = receivedString.find(':', delimiterPos4 + 1);

    if (delimiterPos1 != std::string::npos && delimiterPos2 != std::string::npos && delimiterPos3 != std::string::npos &&
        delimiterPos4 != std::string::npos && delimiterPos5 != std::string::npos)
    {
        receivedData.mode = std::stoi(receivedString.substr(0, delimiterPos1));
        receivedData.choice = std::stoi(receivedString.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1));

        // Extract strings and populate the vectors
        std::string message = receivedString.substr(delimiterPos2 + 1, delimiterPos3 - delimiterPos2 - 1);
        std::string client = receivedString.substr(delimiterPos3 + 1, delimiterPos4 - delimiterPos3 - 1);
        std::string server = receivedString.substr(delimiterPos4 + 1, delimiterPos5 - delimiterPos4 - 1);
        std::string infors = receivedString.substr(delimiterPos5 + 1);

        parseStringToVector(message, receivedData.clientHandCards);
        parseStringToVector(client, receivedData.clientHeroStats);
        parseStringToVector(server, receivedData.serverHeroStats);
        parseStringToVector(infors, receivedData.gameInfos);
    }
    return 0;
}

// void MySocket::sendData(const std::string &data)
// {
//     send(clientSocket_, data.c_str(), data.size(), 0);
// }

void MySocket::initializeServer()
{
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(8080);
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
    serverAddress_.sin_port = htons(8080);
    serverAddress_.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket_, (struct sockaddr *)&serverAddress_, sizeof(serverAddress_)) == -1)
    {
        std::cerr << "Error connecting to the server." << std::endl;
        exit(EXIT_FAILURE);
    }
}