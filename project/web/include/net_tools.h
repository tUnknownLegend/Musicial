#ifndef PROJECT_WEB_INCLUDE_NET_TOOLS_H_
#define PROJECT_WEB_INCLUDE_NET_TOOLS_H_

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "shared_lib.h"


std::ostream &operator<<(std::ostream &os, const Message &message);

namespace net_tools {
    Message getAnswer(const Message &mes);

    Message getMessage();

    std::string Message2String(const Message &message);

    std::vector<std::string> parseMessage(const std::string &s, char delim);

    Message String2Message(const std::string &str);

}  // namespace net_tools

#endif  // PROJECT_WEB_INCLUDE_NET_TOOLS_H_
