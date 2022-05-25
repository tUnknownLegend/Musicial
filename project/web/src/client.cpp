#include "client.h"

int main() {
    std::string ip, port, path;
    std::cout << "Enter IP: ";
    std::cin >> ip;
    std::cout << "Enter port: ";
    std::cin >> port;
    std::cout << "Enter path: ";
    std::cin >> path;

    Message message = net_tools::getMessage();

    try {
        boost::asio::io_context io_context;
        std::cout << "client is working" << std::endl;
        Client c(io_context, ip, port, path, message);
        io_context.run();
    }
    catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
}
