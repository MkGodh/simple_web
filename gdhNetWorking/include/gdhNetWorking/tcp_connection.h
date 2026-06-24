#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>

namespace MOYF {
    using boost::asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection>{

    public:
    using pointer = std::shared_ptr<TCPConnection>;

    static pointer Create(boost::asio::io_context& ioContext){
        return pointer(new TCPConnection(ioContext));
    }
    tcp::socket& socket(){
            return _socket;
        }
    void start();

    private:
        explicit TCPConnection(boost::asio::io_context& ioContext);

        tcp::socket _socket;
        std::string  _message {"Hello, beautiful client!\n"};
     };


    class PROXYConnection : public std::enable_shared_from_this<PROXYConnection>{
    private:
        tcp::socket client_socket;
        tcp::socket remote_socket;
        std::array<char, 1024> buff_client;
        std::array<char, 1024> buff_remote;
    public:
        PROXYConnection(boost::asio::io_context &ioContext);
        bool isAlive = true;
        void start();
        void startClientToRemote();
        void startRemoteToClient();
        void shutDown();
        using pointer = std::shared_ptr<PROXYConnection>;

        tcp::socket& _client(){
            return client_socket;
        }

        tcp::socket& _remote(){
            return remote_socket;
        }

        static pointer Create(boost::asio::io_context& ioContext){
            return pointer(new PROXYConnection(ioContext));
        }

    };
}


