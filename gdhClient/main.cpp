#include <boost/asio.hpp>
#include <iostream>
//#include <gdhNetWorking/Base.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "Russian");
    try{
        boost::asio::io_context ioContext;

        tcp::resolver resolver{ioContext};
        auto  endPoints = resolver.resolve("127.0.0.1", "8080");

        tcp::socket socket {ioContext};
        boost::asio::connect(socket, endPoints);
        boost::system::error_code ec;
        if(ec) {
            std::cerr << "Connect failed: " << ec.message() << std::endl;
        } else {
            std::cout << "Connected!" << std::endl;
        }


        while(true){
            // listen for msg
            std::array<char, 128> buf {};
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if(error == boost::asio::error::eof){
                //client connection off
                break;
            }else if(error){
                throw boost::system::system_error(error);
            }
            std::cout.write(buf.data(), len);

        }

    }catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

