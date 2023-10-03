#ifndef SOCKET_H
#define SOCKET_H

class Socket
{
public:
  Socket();

  void run();

private:
  int serverSocket;
  int clientSocket;
  static const int BUFFER_SIZE = 4096;
  void runHost();
  void runClient();
};

#endif // SOCKET_H
