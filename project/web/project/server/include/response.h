#ifndef PROJECT_SERVER_INCLUDE_RESPONSE_H_
#define PROJECT_SERVER_INCLUDE_RESPONSE_H_

#include <string>
#include <vector>

#include "net_tools.h"


struct Response {
    int status_code;
    std::string status_message;
    std::vector<std::string> headers;
    std::string http_version;

    net_tools::Message body;
};

inline std::ostream &operator<<(std::ostream &os, const Response &response) {
    os << "\nResponse:\n" << response.body << "\n\n";

    return os;
}

inline std::string Response2String(const Response &response) {
    std::stringstream ss;
    ss << response.http_version << " " << response.status_code << " " << response.status_message << "\r\n\r\n";
    ss << net_tools::Message2String(response.body) << "\r\n";

    return ss.str();
}

#endif  // PROJECT_SERVER_INCLUDE_RESPONSE_H_
