#include <iostream>
#include <array>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_context io;

        tcp::acceptor acceptor(
                io,
                tcp::endpoint(tcp::v4(), 9090)
        );

        std::cout << "Listening on 9090\n";

        tcp::socket socket(io);

        acceptor.accept(socket);

        std::cout << "Client connected\n";

        boost::asio::write(
                socket,
                boost::asio::buffer("Hello from test server\n")
        );

        std::array<char, 1024> buffer{};

        while (true)
        {
            boost::system::error_code ec;

            size_t bytes =
                    socket.read_some(
                            boost::asio::buffer(buffer),
                            ec
                    );

            if (ec)
            {
                std::cout << "Disconnected\n";
                break;
            }

            std::cout << "Received: "
                      << std::string(buffer.data(), bytes)
                      << "\n";

            boost::asio::write(
                    socket,
                    boost::asio::buffer(buffer.data(), bytes)
            );
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}