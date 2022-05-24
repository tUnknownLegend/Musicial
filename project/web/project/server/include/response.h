#ifndef PROJECT_SERVER_INCLUDE_RESPONSE_H_
#define PROJECT_SERVER_INCLUDE_RESPONSE_H_

#include <vector>
#include <string>
#include "net_tools.h"


struct Response {
    int status_code;
    std::string status_message;
    std::vector<std::string> headers;
    std::string http_version;

    net_tools::Message body;
};

inline std::ostream &operator<<(std::ostream &os, const Response &response) {
    /*
    os << response.status_code << std::endl;
    os << response.http_version << std::endl;
    for (int i = 0; i < (int) response.headers.size(); i++)
        os << response.headers[i] << std::endl;
    */

    os << "\nResponse:\n" << response.body << "\n\n";

    return os;
}

inline std::string Response2String(const Response &response) {
    std::stringstream ss;
    ss << response.http_version << " " << response.status_code << " " << response.status_message << "\r\n\r\n";
    ss << net_tools::Message2String(response.body) << "\r\n\r\n";

    return ss.str();
}

#endif  // PROJECT_SERVER_INCLUDE_RESPONSE_H_
