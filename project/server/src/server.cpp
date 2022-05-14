#include "server_tools.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char *argv[]) {
    std::cout << "Info: 'hostname -I' to get local ip" << std::endl;
    try {
        // Check command line arguments.
        if (argc != 3) {
            std::cerr << "Usage: http_server <address> <port>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80 \n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80 \n";
            return 1;
        }
/*
    std::string ip, port;
    std::cout << "Enter IP: ";
    std::cin >> ip;

    std::cout << "Enter port: ";
    std::cin >> port;
*/
        // Initialise the server.

        // std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
        std::size_t num_threads = 2 * (std::size_t) sysconf(_SC_NPROCESSORS_ONLN);
        http::server3::server s(argv[1], argv[2], num_threads);

        // Run the server until stopped.
        s.run();
    }


    catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}

