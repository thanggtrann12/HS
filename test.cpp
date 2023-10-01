#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main()
{
    io_service service;

    // Create an acceptor to listen for incoming connections
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 12345));

    std::cout << "Server listening on port 12345..." << std::endl;

    // Accept incoming connections
    ip::tcp::socket socket(service);
    acceptor.accept(socket);

    std::cout << "Client connected." << std::endl;

    // Send and receive data here...

    // Close the socket
    socket.close();

    return 0;
}
