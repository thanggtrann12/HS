#ifndef IP_H
#define IP_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

std::string GetLocalIP()
{
  std::string localIP = "127.0.0.1"; // Default to localhost IP

#ifdef _WIN32
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
  {
    std::cerr << "Failed to initialize Winsock." << std::endl;
    return localIP;
  }

  char hostname[1024];
  if (gethostname(hostname, sizeof(hostname)) != 0)
  {
    std::cerr << "Error getting hostname." << std::endl;
    WSACleanup();
    return localIP;
  }

  struct hostent *host;
  host = gethostbyname(hostname);
  if (host == nullptr)
  {
    std::cerr << "Error getting host info." << std::endl;
    WSACleanup();
    return localIP;
  }

  in_addr addr;
  memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));
  localIP = inet_ntoa(addr);
  WSACleanup();
#else
  char hostname[256];
  if (gethostname(hostname, sizeof(hostname)) != 0)
  {
    std::cerr << "Error getting hostname." << std::endl;
    return localIP;
  }

  struct addrinfo hints, *info, *p;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(hostname, nullptr, &hints, &info) != 0)
  {
    std::cerr << "Error getting address info." << std::endl;
    return localIP;
  }

  for (p = info; p != nullptr; p = p->ai_next)
  {
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
    localIP = inet_ntoa(ipv4->sin_addr);
    break; // Get the first IP address
  }

  freeaddrinfo(info);
#endif

  return localIP;
}

// Function to split a string into a vector of strings based on a delimiter
std::vector<std::string> split(const std::string &s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

// Function to sum the octets of an IP address
int sumOctets(const std::string &ipAddress)
{
  // Split the IP address into octets using '.' as the delimiter
  std::vector<std::string> octets = split(ipAddress, '.');

  // Initialize the sum
  int sum = 0;

  // Convert each octet to an integer and add it to the sum
  for (const std::string &octet : octets)
  {
    int octetValue = std::stoi(octet);
    sum += octetValue;
  }

  return sum;
}

#endif