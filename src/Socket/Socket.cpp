#include "Socket/Socket.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits>
#include "Socket/Ip.h"
const int PORT = 8081;
const int BUFFER_SIZE = 1024;

Socket::Socket() : serverSocket(-1), clientSocket(-1) {}

void Socket::run()
{
  std::cout << "Choose an option:" << std::endl;
  std::cout << "1. Host" << std::endl;
  std::cout << "2. Client" << std::endl;

  int choice;
  std::cin >> choice;

  if (choice == 1)
  {
    runHost();
  }
  else if (choice == 2)
  {
    runClient();
  }
  else
  {
    std::cout << "Invalid choice." << std::endl;
    return;
  }

  if (clientSocket != -1)
  {
    close(clientSocket);
  }

  if (serverSocket != -1)
  {
    close(serverSocket);
  }

  std::cout << "Socket is shutting down..." << std::endl;
}

void Socket::runHost()
{
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t addrSize = sizeof(clientAddr);

  // Create socket
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
  {
    perror("Socket creation error");
    return;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // Bind socket
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    perror("Binding error");
    return;
  }

  if (listen(serverSocket, 1) < 0)
  {
    perror("Listen error");
    return;
  }

  std::cout << "Server socket created..." << std::endl;
  std::cout << "Waiting for a client to connect..." << std::endl;

  // Accept a client connection
  clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
  if (clientSocket < 0)
  {
    perror("Accept error");
    return;
  }

  std::cout << "Client connected..." << std::endl;

  char buffer[BUFFER_SIZE];
  while (true)
  {
    // Host's turn
    std::cout << "Host's turn. Enter a message: ";
    std::string hostMessage;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::getline(std::cin, hostMessage);

    send(clientSocket, hostMessage.c_str(), hostMessage.size(), 0);
    std::cout << "Wait for Client turn's" << std::endl;
    if (hostMessage == "exit")
    {
      break;
    }

    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Received from client: " << buffer << std::endl;

    // Check for game over condition and exit the loop if needed
    if (hostMessage == "gameover")
    {
      break;
    }
  }

  // Close sockets
  close(clientSocket);
  close(serverSocket);

  std::cout << "Server is shutting down..." << std::endl;
}

void Socket::runClient()
{
  struct sockaddr_in serverAddr;

  // Create socket
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0)
  {
    perror("Socket creation error");
    return;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr(GetLocalIP().c_str()); // Set the server IP here.

  if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    perror("Connection error");
    return;
  }

  std::cout << "Connected to the server..." << std::endl;

  char buffer[BUFFER_SIZE];
  while (true)
  {
    // Client's turn
    std::cout << "Waiting for server's turn..." << std::endl;
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Received from server: " << buffer << std::endl;

    // Check for game over condition and exit the loop if needed
    if (std::string(buffer) == "gameover")
    {
      send(clientSocket, "gameover", 8, 0);
      exit(0);
    }

    // Client's turn to send a message
    std::cout << "Client's turn. Enter a message: ";
    std::string clientMessage;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::getline(std::cin, clientMessage);

    send(clientSocket, clientMessage.c_str(), clientMessage.size(), 0);

    if (clientMessage == "exit")
    {
      break;
    }
  }

  // Close the socket
  close(clientSocket);

  std::cout << "Client is shutting down..." << std::endl;
}
