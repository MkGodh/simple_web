#include "gdhNetWorking/tcp_connection.h"

namespace MOYF{
    TCPConnection::TCPConnection(boost::asio::io_context &ioContext)  : _socket(ioContext){

    }

    void TCPConnection::start() {
        auto strongThis = shared_from_this();
        boost::asio::async_write(socket(), boost::asio::buffer(_message),
        [strongThis ](const boost::system::error_code& error, size_t bytesTransferred){
            if(error){
                std::cout << "Failed to send message!\n";
            }else{
                std::cout << "Sent " << bytesTransferred << " bytes of data!\n";
            }
        });

        boost::asio::streambuf buffer;

        _socket.async_receive(buffer.prepare(512), [this](const boost::system::error_code& error, size_t bytesTransfered){
            if(error == boost::asio::error::eof){
                //client connection off
                std::cout << "Client disconnected properly!\n";
            }else if(error){
                std::cout << "Client disconnected in bad way!\n";
              //  throw boost::system::system_error(error);
            }
        });
    }
}