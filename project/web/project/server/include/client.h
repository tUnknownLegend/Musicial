#include "client_tools.h"

namespace client {
    void sendMessage(const std::string &ip, const std::string &port, const std::string &path,
                    const net_tools::Message &message) {
        client_tools::send(ip, port, path, message);

    }
}
