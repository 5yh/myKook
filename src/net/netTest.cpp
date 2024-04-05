#pragma once
#pragma execution_character_set("utf-8")
#include <asio.hpp>
#include <iostream>
#include <SDL.h>
#include "../../include/SDLSpeaker.h"
using asio::ip::tcp;

constexpr int stream_length = 1024;
class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}
    void setSpeaker(SDLSpeaker &speaker)
    {
        this->speaker = &speaker;
    }
    void start()
    {
        // std::cout << "session start";
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(asio::buffer(data_, stream_length),
                                [this, self](const asio::error_code &error, size_t length)
                                {
                                    if (!error)
                                    {
                                        // std::cout << "receive\n";
                                        // std::cout << "do read huidiao\n";
                                        //  do something with the received data if needed
                                        // std::cout << data_;
                                        if (speaker)
                                        {
                                            // 假设 SDLSpeaker 有一个叫做 getValue() 的方法
                                            // int value = speaker->getValue();
                                            // std::cout << "Value from SDLSpeaker: " << value << std::endl;
                                            // std::cout << data_;
                                            // std::cout << "receive1\n";
                                            // std::cout << speaker->getSpeakerID();
                                            // std::cout << SDL_GetQueuedAudioSize(speaker->getSpeakerID()) << std::endl;
                                            SDL_QueueAudio(speaker->getSpeakerID(), data_, length);
                                            std::cout << SDL_GetError();
                                            // std::cout << length;
                                        }

                                        do_read(); // Continue reading
                                    }
                                });
    }

    tcp::socket socket_;
    Uint8 data_[stream_length];
    SDLSpeaker *speaker;
};
class Server
{
public:
    Server(asio::io_context &io_context, short port, SDLSpeaker *speaker)
        : acceptor_(io_context, tcp::endpoint(tcp::v6(), port)), socket_(io_context), speaker(speaker)
    {
        // std::cout << "ni1";
        //acceptor_.set_option(asio::ip::v6_only(false));
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept(socket_, [this](const asio::error_code &error)
                               {
            if (!error) {

                // std::make_shared<Session>(std::move(socket_))->start();
                auto session = std::make_shared<Session>(std::move(socket_));
                session->setSpeaker(*speaker); // 在这里调用 setSpeaker 方法
                session->start();

                /*std::cout << "if!ersssssssssror\n";*/
            }

            do_accept(); });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    SDLSpeaker *speaker;
};

class Client
{
public:
    Client(asio::io_context &io_context, const std::string &host, const std::string &port)
        : socket_(io_context)
    {
        tcp::resolver resolver(io_context);
        asio::connect(socket_, resolver.resolve(host, port));
    }

    void send_data(Uint8 *data, int length)
    {
        // std::cout << "sending" << std::endl;
        asio::write(socket_, asio::buffer(data, length));
    }

private:
    tcp::socket socket_;
};
