
#include "gdhNetWorking/tcp_server.h"
#include <iostream>

namespace MOYF {
  using  boost::asio::ip::tcp;
    TCPserver::TCPserver(IPV ipv, int port) : _ipVersion(ipv), _port(port),
    _acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), _port)){


    }

    int TCPserver::Run() {
        try {
            startAccept();
            _ioContext.run();
        }catch (std::exception& e){
            std::cerr << e.what() << std::endl;
            return -1;
        }
        return 0;
    }

    void TCPserver::startAccept() {
        //create connection
        auto connection = TCPConnection::Create(_ioContext);

        _connections.push_back(connection);
        //asynchronous accept the connecttion
        _acceptor.async_accept(connection->socket(), [connection, this](const boost::system::error_code& error){
            if(!error){
                connection ->start();
            }
            startAccept();
        });




    }
}