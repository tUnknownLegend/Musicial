#ifndef PROJECT_SERVER_INCLUDE_CONNECTION_H_
#define PROJECT_SERVER_INCLUDE_CONNECTION_H_

#include <memory>

#include "response.h"
#include "request.h"
#include "router.h"

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


namespace http {
namespace server3 {

class Connection
        : public boost::enable_shared_from_this<Connection>,
          private boost::noncopyable {
 public:
    /// Construct a connection with the given io_context.
    explicit Connection(boost::asio::io_context &io_context,
                        Router<Response(*)(const Request &request)> &requestRouter);

    /// Get the socket associated with the connection.
    boost::asio::ip::tcp::socket &socket();

    /// Start the first asynchronous operation for the connection.
    void start();

 private:
    /// Handle completion of a read operation.
    void handle_read(const boost::system::error_code &e,
                     std::size_t bytes_transferred);

    /// Handle completion of a write operation.
    void handle_write(const boost::system::error_code &e);

 private:
    /// Strand to ensure the connection's handlers are not called concurrently.
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;

    /// Socket for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// The handler used to process the incoming request.
    Router<Response(*)(const Request &request)> &requestRouter_;

    /// Buffer for incoming data.
    boost::array<char, 8192> buffer_;

    /// The incoming request.
    Request request_;

    /// The response to be sent back to the client.
    Response response_;
};

}  // namespace server3

}  // namespace http

#endif  // PROJECT_SERVER_INCLUDE_CONNECTION_H_
