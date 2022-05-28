#ifndef PROJECT_WEB_INCLUDE_ROUTER_H_
#define PROJECT_WEB_INCLUDE_ROUTER_H_

#include <map>
#include <string>

namespace http {
namespace server3 {
template<typename Handler>
class Router {
 public:
    void addHandler(std::string method, Handler handler) {
        m_Handlers.emplace(method, handler);
    }

    Response processRoute(const std::string &method, const Request &request) {
        auto handler_it = m_Handlers.find(method);
        if (handler_it != m_Handlers.end()) {
            return (handler_it->second)(request);
        }

        Response response;

        response.status_code = 404;
        response.status_message = "Not Found";
        response.http_version = "HTTP/1.0";


        return response;
    }

 private:
    std::map<std::string, Handler> m_Handlers;
};

}  // namespace server3

}  // namespace http


#endif  // PROJECT_WEB_INCLUDE_ROUTER_H_
