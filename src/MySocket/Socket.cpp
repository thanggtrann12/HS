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

void MySocket::sendInitCardPool(const Card::CardType *entities)
{
  size_t arraySize = 20;
  ssize_t sentBytes = send(clientSocket_, entities, arraySize * sizeof(Card::CardType), 0);
}
// std::shared_ptr<Card> createMinionFromEntityType(Card::CardType entity)
// {
//   switch (entity)
//   {
//   case Card::CardType::FIRELORD:
//     return std::make_shared<RagnarosTheFirelord>();
//   case Card::CardType::THALNOS:
//     return std::make_shared<BloodmageThalnos>();
//   case Card::CardType::BRAWL:
//     return std::make_shared<Brawl>();
//   case Card::CardType::TECHIES:
//     return std::make_shared<Techies>();
//   case Card::CardType::SHAMAN:
//     return std::make_shared<FlametongueTotem>();
//   default:
//     return nullptr;
//   }
// }
bool MySocket::receiveInitCardPool(std::vector<std::shared_ptr<Card>> &client, std::vector<std::shared_ptr<Card>> &server)
{
  // Card::CardType entities[20];
  // size_t arraySize = 20;
  // client.clear();
  // server.clear();
  // ssize_t receivedBytes = recv(clientSocket_, entities, arraySize * sizeof(Card::CardType), 0);

  // if (receivedBytes == -1)
  // {
  //   perror("Receive failed");
  //   return false;
  // }
  // else if (receivedBytes == 0)
  // {
  //   return false;
  // }

  // for (size_t i = 0; i < 10; i++)
  // {
  //   std::shared_ptr<Card> minion = createMinionFromEntityType(entities[i]);
  //   if (minion)
  //   {
  //     client.emplace_back(minion);
  //   }
  // }

  // for (size_t i = 10; i < 20; i++)
  // {
  //   std::shared_ptr<Card> minion = createMinionFromEntityType(entities[i]);
  //   if (minion)
  //   {
  //     server.emplace_back(minion);
  //   }
  // }

  return true;
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