#ifndef PROJECT_WEB_INCLUDE_CLIENT_TOOLS_H_
#define PROJECT_WEB_INCLUDE_CLIENT_TOOLS_H_


#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "net_tools.h"
#include "request.h"
#include "response.h"

using boost::asio::ip::tcp;


class Client {
 public:
    Client(boost::asio::io_context &io_context,
           const std::string &server, const std::string &port, const std::string &path,
           const sharedLib::Message &message, std::function<void(const sharedLib::Message &Message)> a)
            : resolver_(io_context),
              socket_(io_context), sendResponse(std::move(a)) {
        request_.method = "GET";
        request_.path = path;
        request_.http_version = "HTTP/1.0";
        request_.host = server;
        request_.body = message;


        resolver_.async_resolve(server, port,
                                boost::bind(&Client::handle_resolve, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::results));
    }


 private:

    void handle_resolve(const boost::system::error_code &err,
                        const tcp::resolver::results_type &endpoints) {
        if (!err) {
            boost::asio::async_connect(socket_, endpoints,
                                       boost::bind(&Client::handle_connect, this,
                                                   boost::asio::placeholders::error));
        } else {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_connect(const boost::system::error_code &err) {
        if (!err) {
            std::string buffer = Request2String(request_);

            boost::asio::async_write(socket_, boost::asio::buffer(buffer.data(), buffer.size()),
                                     boost::bind(&Client::handle_write_request, this,
                                                 boost::asio::placeholders::error));

        } else {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_write_request(const boost::system::error_code &err) {
        if (!err) {
            boost::asio::async_read_until(socket_, response_buf_, "\r\n",
                                          boost::bind(&Client::handle_read_status_line, this,
                                                      boost::asio::placeholders::error));
        } else {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_read_status_line(const boost::system::error_code &err) {
        if (!err) {
            // Check that response is OK.
            std::istream response_stream(&response_buf_);
            response_stream >> response_.http_version;
            response_stream >> response_.status_code;
            std::getline(response_stream, response_.status_message);


            if (response_.status_code != 200) {
                std::cout << "Response returned with status code ";
                std::cout << response_.status_code << "\n";
                return;
            }

            boost::asio::async_read_until(socket_, response_buf_, "\r\n\r\n",
                                          boost::bind(&Client::handle_read_headers, this,
                                                      boost::asio::placeholders::error));
        } else {
            std::cout << "Error: " << err << "\n";
        }
    }

    void handle_read_headers(const boost::system::error_code &err) {
        if (!err) {
            std::istream response_stream(&response_buf_);

            std::string header;
            while (std::getline(response_stream, header) && header != "\r")
                response_.headers.push_back(header);

            boost::asio::async_read(socket_, response_buf_,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&Client::handle_read_content, this,
                                                boost::asio::placeholders::error));
        } else {
            std::cout << "Error: " << err << "\n";
        }
    }

    void handle_read_content(const boost::system::error_code &err) {
        if (!err) {
            boost::asio::async_read(socket_, response_buf_,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&Client::handle_read_content, this,
                                                boost::asio::placeholders::error));

        } else if (err == boost::asio::error::eof) {
            std::istream response_stream(&response_buf_);

            response_.body = net_tools::String2Message(std::string(
                    std::istreambuf_iterator<char>(response_stream), std::istreambuf_iterator<char>()));
            std::cout << response_;

            sendResponse(response_.body);

        } else {
            std::cout << "Error: " << err << "\n";
        }
    }

    std::function<void(const sharedLib::Message &Message)> sendResponse;

    tcp::resolver resolver_;
    tcp::socket socket_;

    boost::asio::streambuf response_buf_;

    Request request_;
    Response response_;
};

namespace client_tools {
    int send(const std::string &ip, const std::string &port, const std::string &path,
             const sharedLib::Message &message, std::function<void(const sharedLib::Message &Message)> a) {
        try {
            boost::asio::io_context io_context;
            std::cout << "client is working" << std::endl;
            Client c(io_context, ip, port, path, message, std::move(a));
            io_context.run();
        }
        catch (std::exception &e) {
            std::cout << "Exception: " << e.what() << "\n";
        }

        return 0;
    }

    void pushResponse(const sharedLib::Message &message) {
        // do something on client side
    }

}  // namespace client_tools

#endif  // PROJECT_WEB_INCLUDE_CLIENT_TOOLS_H_
