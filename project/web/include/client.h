#ifndef PROJECT_WEB_INCLUDE_CLIENT_H_
#define PROJECT_WEB_INCLUDE_CLIENT_H_

#include <string>

#include "client_tools.h"

namespace webClient {
    void sendMessage(const std::string &ip, const std::string &port, const std::string &path,
                     const sharedLib::Message &message, std::function<void(const sharedLib::Message &Message)> a) {
        client_tools::send(ip, port, path, message, std::move(a));
        //std::cout << "HAHAHA";
    }
}


#endif  // PROJECT_WEB_INCLUDE_CLIENT_H_
