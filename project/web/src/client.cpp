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
    client::sendMessage(ip, port, path, message);
}
