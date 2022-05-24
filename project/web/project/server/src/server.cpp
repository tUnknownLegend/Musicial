#include "server_tools.h"
#include "client.h"


int main() {
    server_tools::startServer();
    //net_tools::Message message = net_tools::getMessage();
    //webClient::sendMessage("0.0.0.0", "5000", "/test", message);

    return 0;
}

