#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/spawn.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;

using tcp = asio::ip::tcp;

// WebSocket服务器
class WebsocketServer
{
public:
    WebsocketServer(asio::io_context &io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), socket_(io_context) {}

    void start(asio::yield_context yield)
    {
        while (true)
        {
            acceptor_.async_accept(socket_, yield);
            asio::spawn(acceptor_.get_executor(), std::bind(&WebsocketServer::session, this, std::placeholders::_1));
        }
    }

    void session(asio::yield_context yield)
    {
        try
        {
            while (true)
            {
                beast::flat_buffer buffer;
                websocket::stream<tcp::socket &> ws(socket_);
                ws.async_accept(yield);

                for (;;)
                {
                    beast::error_code ec;
                    ws.async_read(buffer, yield[ec]);
                    if (ec == websocket::error::closed)
                    {
                        break;
                    }
                    if (ec)
                    {
                        throw beast::system_error{ec};
                    }

                    ws.text(ws.got_text());
                    ws.async_write(buffer.data(), yield[ec]);
                    if (ec)
                    {
                        throw beast::system_error{ec};
                    }
                }
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

// WebSocket客户端
class WebsocketClient
{
public:
    WebsocketClient(asio::io_context &io_context, const std::string &host, const std::string &port)
        : resolver_(io_context), socket_(io_context)
    {
        resolver_.async_resolve(host, port, asio::use_awaitable);
    }

    void connect(asio::yield_context yield)
    {
        auto endpoints = resolver_.async_resolve(asio::use_awaitable);
        asio::async_connect(socket_, endpoints, yield);
        ws_.emplace(std::move(socket_));
        ws_->async_handshake(host_, "/", asio::use_awaitable);
    }

    void send(const std::string &message, asio::yield_context yield)
    {
        ws_->text(true);
        ws_->async_write(asio::buffer(message), yield);
    }

    std::string receive(asio::yield_context yield)
    {
        beast::flat_buffer buffer;
        ws_->async_read(buffer, yield);
        return beast::buffers_to_string(buffer.data());
    }

private:
    tcp::resolver resolver_;
    tcp::socket socket_;
    std::optional<websocket::stream<tcp::socket>> ws_;
    beast::string_view host_;
};

int main()
{
    try
    {
        asio::io_context io_context;

        // 启动服务器
        WebsocketServer server(io_context, 8080);
        asio::spawn(io_context, [&server](asio::yield_context yield)
                    { server.start(yield); });

        // 连接客户端
        WebsocketClient client(io_context, "localhost", "8080");
        asio::spawn(io_context, [&client](asio::yield_context yield)
                    { client.connect(yield); });

        // 向服务器发送消息，并接收响应
        asio::spawn(io_context, [&client](asio::yield_context yield)
                    {
            client.send("Hello from client", yield);
            std::string response = client.receive(yield);
            std::cout << "Server response: " << response << std::endl; });

        io_context.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
