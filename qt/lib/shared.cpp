#include "shared_lib.h"
#include <functional>
// shared function
namespace webClient {
    void sendMessage(const std::string &ip, const std::string &port, const std::string &path,
                     const sharedLib::Message &message,
                     const std::function<void(const sharedLib::Message &Message)>& a) {
        std::cout << "webClient::sendMessage\n";
    }
}
// end shared function
