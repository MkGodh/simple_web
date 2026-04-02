#include <iostream>
#include <gdhNetWorking/tcp_server.h>


using boost::asio::ip::tcp;
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    MOYF::TCPserver server{MOYF::IPV::V4, 8080};

    server.Run();

    return 0;
}