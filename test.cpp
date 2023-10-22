#include <iostream>
#include <string>
#include <vector>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
struct data_t
{
    int mode;
    int choice;
    std::vector<std::string> clientHandCards;
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

    ~MySocket()
    {
        if (clientSocket_ != -1)
        {
            close(clientSocket_);
        }
    }

    void sendData()
    {
        // Implement your sendData logic here
    }

    int receiveData(data_t &receivedData)
    {
        // Implement your receiveData logic here
        return 0; // Placeholder, replace with actual code
    }

    void sendData(const data_t &data)
    {
        // Implement your sendData logic here
    }

private:
    int mode_;
    int serverSocket_;
    int clientSocket_;
    sockaddr_in serverAddress_;
    sockaddr_in clientAddress_;

    void initializeServer()
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

    void initializeClient()
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
};

int main()
{
    int mode; // Change mode as needed (1 for server, 2 for client)
    std::cin >> mode;
    MySocket socket(mode);

    while (true)
    {
        data_t receivedData;
        socket.receiveData(receivedData);

        // Implement your processing logic here

        socket.sendData(receivedData);
    }

    return 0;
}
