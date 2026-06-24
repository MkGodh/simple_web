#include "gdhNetWorking/tcp_connection.h"

namespace MOYF {
    TCPConnection::TCPConnection(boost::asio::io_context &ioContext) : _socket(ioContext) {}

    PROXYConnection::PROXYConnection(boost::asio::io_context &ioContext) :
            client_socket(ioContext), remote_socket(ioContext) {}

    void PROXYConnection::shutDown() {
        client_socket.close();
        remote_socket.close();
        isAlive = false;
    }

    void TCPConnection::start() {
        auto strongThis = shared_from_this();
        boost::asio::async_write(socket(), boost::asio::buffer(_message),
                                 [strongThis](const boost::system::error_code &error, size_t bytesTransferred) {
                                     if (error) {
                                         std::cout << "Failed to send message!\n";
                                     } else {
                                         std::cout << "Sent " << bytesTransferred << " bytes of data!\n";
                                     }
                                 });

        boost::asio::streambuf buffer;

        _socket.async_receive(buffer.prepare(512),
                              [strongThis](const boost::system::error_code &error, size_t bytesTransfered) {
                                  if (error == boost::asio::error::eof) {
                                      //client connection off
                                      std::cout << "Client disconnected properly!\n";
                                  } else if (error) {
                                      std::cout << "Client disconnected in bad way!\n";
                                      //  throw boost::system::system_error(error);
                                  }
                              });
    }

    void PROXYConnection::startClientToRemote() {

        client_socket.async_read_some(boost::asio::buffer(buff_client, 1024),
                                      [self = shared_from_this()](const boost::system::error_code &error,
                                                                  size_t bytesTransfered) {

                          if (error) {
                              std::cout << "Connect failed: " << error.message() << "\n";
                              self->shutDown();
                              return;
                          }
                          boost::asio::async_write(self->remote_socket,
                                                   boost::asio::buffer(self->buff_client,
                                                                       bytesTransfered),
                                                   [self](const boost::system::error_code &error,
                                                          size_t bytesTransfered) {
                                                       if (!self->isAlive) {
                                                           return;
                                                       }

                                                       if (error) {
                                                           std::cout << "Connect failed: "
                                                                     << error.message() << "\n";

                                                           self->shutDown();
                                                           return;
                                                       }
                                                       self->startClientToRemote();
                                                   });
                                      });
    }

    void PROXYConnection::startRemoteToClient() {

        remote_socket.async_read_some(boost::asio::buffer(buff_remote, 1024),
                                      [self = shared_from_this()](const boost::system::error_code &error,
                                                                  size_t bytesTransfered) {
                  if (error) {
                      std::cout << "Connect failed: " << error.message() << "\n";
                      self->shutDown();
                      return;
                  }

                  boost::asio::async_write(self->client_socket,
                                           boost::asio::buffer(self->buff_remote,
                                                               bytesTransfered),
                                           [self](const boost::system::error_code &error,
                                                  size_t bytesTransfered) {
                                               if (!self->isAlive) {
                                                   return;
                                               }

                                               if (error) {
                                                   std::cout << "Connect failed: "
                                                             << error.message() << "\n";
                                                   self->shutDown();
                                                   return;

                                               }
                                               self->startRemoteToClient();
                                           });
                                      });
    }

    void PROXYConnection::start() {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("127.0.0.1"), 9090);

        remote_socket.async_connect(endpoint, [self = shared_from_this()](boost::system::error_code ec) {
            if (!ec) {                                                                                                                              // Connection CS -> RS , RS -> CS  Дальше RS->CS функция
                std::cout << "Connected to remote server\n";

                self->startClientToRemote();
                self->startRemoteToClient();


            } else {
                std::cout << "Connect failed: " << ec.message() << "\n";
            }
        });
    }
}