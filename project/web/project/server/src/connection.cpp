#include "connection.h"

#include <boost/bind/bind.hpp>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


Request parse(const std::string &req_data) {
    Request request;
    std::vector<std::string> blocks = split(req_data, '\n');

    // first line
    std::vector<std::string> data = split(blocks[0], ' ');


    request.method = data[0];
    request.path = data[1];
    request.http_version = data[2];

    int beginPos = req_data.find("\r\n\r\n");
    std::string msg = req_data.substr(beginPos+4);
    request.body = net_tools::String2Message(msg);

    return request;
}


namespace http {
namespace server3 {

Connection::Connection(boost::asio::io_context &io_context,
                       Router<Response(*)(const Request &request)> &requestRouter)
        : strand_(boost::asio::make_strand(io_context)),
          socket_(strand_),
          requestRouter_(requestRouter),
          response_(),
          request_() {
}

boost::asio::ip::tcp::socket &Connection::socket() {
    return socket_;
}

void Connection::start() {
    socket_.async_read_some(boost::asio::buffer(buffer_),
                            boost::bind(&Connection::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void Connection::handle_read(const boost::system::error_code &e,
                             std::size_t bytes_transferred) {
    if (!e) {
        std::cout << buffer_.data() << std::endl;
        Request request = parse(std::string(buffer_.data()));

        Response response = requestRouter_.processRoute(request.path, request);
        std::string buffer = Response2String(response);
        boost::asio::async_write(socket_, boost::asio::buffer(buffer.data(), buffer.size()),
                                 boost::bind(&Connection::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error));


    }
}

void Connection::handle_write(const boost::system::error_code &e) {
    if (!e) {
        // Initiate graceful connection closure.
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }
}
}  // namespace server3
}  // namespace http
