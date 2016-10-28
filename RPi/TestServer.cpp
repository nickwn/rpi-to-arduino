#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: \n" << argv[0] << " <port>" << std::endl;
    }

    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), atoi(argv[1])));
    tcp::socket socket(io_service);
    acceptor.accept(socket);

    while(true)
    {
        std::cout << "Enter a message to send: ";
        std::string msg;
        std::cin >> msg;
        boost::asio::write(socket, boost::asio::buffer(msg + "\n"));
    }
    return 0;
}
