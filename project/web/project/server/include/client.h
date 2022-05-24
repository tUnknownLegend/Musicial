#include <utility>

#include "client_tools.h"


namespace webClient {
    void sendMessage(const std::string &ip, const std::string &port, const std::string &path,
                     const net_tools::Message &message, std::function<void(const net_tools::Message &Message)> a) {
        client_tools::send(ip, port, path, message, std::move(a));
        //std::cout << "HAHAHA";
    }
}
