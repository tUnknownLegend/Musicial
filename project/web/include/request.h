#ifndef PROJECT_WEB_INCLUDE_REQUEST_H_
#define PROJECT_WEB_INCLUDE_REQUEST_H_

#include <string>
#include <vector>

#include "net_tools.h"


struct Request {
    std::string host;
    std::string method;
    std::string path;
    std::vector<std::string> params;
    std::vector<std::string> headers;
    std::string http_version;

    Message body;
};

inline std::ostream &operator<<(std::ostream &os, const Request &request) {
    os << "\nRequest:\n" << request.body << "\n\n";

    return os;
}

inline std::string Request2String(const Request &request) {
    std::stringstream ss;

    ss << request.method << " " << request.path << " " << request.http_version << "\r\n";
    ss << "Host: " << request.host << "\r\n";

    for (const auto &header : request.headers) {
        ss << header << "\r\n";
    }

    ss << "\r\n";

    if (!(request.body.text.empty() && request.body.playlists.empty() && request.body.songs.empty())) {
        ss << net_tools::Message2String(request.body) << "\r\n\r\n";
    }

    return ss.str();
}

#endif  // PROJECT_WEB_INCLUDE_REQUEST_H_
