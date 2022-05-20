#ifndef PROJECT_SERVER_INCLUDE_REQUEST_H_
#define PROJECT_SERVER_INCLUDE_REQUEST_H_

#include <vector>
#include <string>

#include "net_tools.h"


struct Request {
    std::string host;
    std::string method;
    std::string path;
    std::vector<std::string> params;
    std::vector<std::string> headers;
    std::string http_version;

    net_tools::Message body;
};

inline std::ostream &operator<<(std::ostream &os, const Request &request) {
    /*
    os << request.method << std::endl;
    os << request.http_version << std::endl;
    for (int i = 0; i < (int) request.headers.size(); i++)
        os << request.headers[i] << std::endl;
    */
    os << "Request:\n" << request.body << "\n\n";

    return os;
}

inline std::string Request2String(const Request &request) {
    std::stringstream ss;

    ss << request.method << " " << request.path << " " << request.http_version << "\r\n";
    ss << "Host: " << request.host << "\r\n";

    for (int i = 0; i < (int) request.headers.size(); i++) {
        ss << request.headers[i] << "\r\n";
    }

    ss << "\r\n";

    if (!net_tools::isMessageEmpty(request.body))
        ss << net_tools::Message2String(request.body) << "\r\n\r\n";

    return ss.str();
}

#endif  // PROJECT_SERVER_INCLUDE_REQUEST_H_
