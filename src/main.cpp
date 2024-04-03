#include <SDL.h>
#include <iostream>
#include <locale.h>
#include "../include/SDLSpeaker.h"
#include "../include/SDLMic.h"
#include <thread>
#include <asio.hpp>
using asio::ip::tcp;

class TCPServer
{
private:
    asio::io_context io_context;
    tcp::acceptor acceptor;
    tcp::socket socket;
    std::vector<int> received_array;

public:
    TCPServer(int port)
        : acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
          socket(io_context)
    {

        acceptor.accept(socket);
        std::cout << "nihao";
        int array_size;
        asio::read(socket, asio::buffer(&array_size, sizeof(array_size)));

        received_array.resize(array_size);
        asio::read(socket, asio::buffer(received_array));
    }

    std::vector<int> receiveArray()
    {
        return received_array;
    }
};

class TCPClient
{
private:
    asio::io_context io_context;
    tcp::socket socket;

public:
    TCPClient(const std::string &ip, int port)
        : socket(io_context)
    {
        tcp::resolver resolver(io_context);
        asio::connect(socket, resolver.resolve(ip, std::to_string(port)));

        std::vector<int> arrayToSend = {1, 2, 3, 4, 5};
        int array_size = arrayToSend.size();
        asio::write(socket, asio::buffer(&array_size, sizeof(array_size)));
        asio::write(socket, asio::buffer(arrayToSend));
    }
};
void recordWithMic(SDLMic *sdlmic)
{
    sdlmic->startRecording();
}

void playWithSpeaker(SDLSpeaker *sdlspeaker)
{
    sdlspeaker->startPlayBack();
}
int main2()
{
    const int port = 8080;
    std::thread server_thread([&]()
                              {
        TCPServer server(port);
        std::vector<int> receivedArray = server.receiveArray();
        std::cout << "Received array: ";
        for (int num : receivedArray) {
            std::cout << num << " ";
        }
        std::cout << std::endl; });

    std::thread client_thread([&]()
                              { TCPClient client("127.0.0.1", port); });

    server_thread.join();
    client_thread.join();

    return 0;
}
int main1()
{
    setlocale(LC_ALL, ".65001"); // 设置当前区域为UTF-8
    SDL_version v;
    SDL_GetVersion(&v);
    std::cout << "SDL version " << int(v.major) << "." << int(v.minor) << "." << int(v.patch) << std::endl;
    // 初始化
    if (SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    SDLMic *sdlmic = new SDLMic();
    sdlmic->showMicDevices();
    // sdlmic->showMicDevice(0);
    sdlmic->chooseMicDevice();
    sdlmic->setDesiredSpec();
    sdlmic->initAudioDevice();
    // sdlmic->startRecording();
    // sdlmic->startSaveWav();

    std::cout << "---------------------------------------------------" << std::endl;
    SDLSpeaker *sdlspeaker = new SDLSpeaker();
    sdlspeaker->showSpeakerDevices();
    // sdlspeaker->showSpeakerDevice(0);
    sdlspeaker->chooseSpeakerDevice();
    sdlspeaker->setDesiredSpec();
    sdlspeaker->initAudioDevice();
    // sdlspeaker->setMic(*sdlmic);
    sdlmic->setSpeaker(*sdlspeaker);
    // sdlspeaker->startPlayBack();
    // 多线程
    std::thread recordThread(recordWithMic, sdlmic);
    std::thread playThread(playWithSpeaker, sdlspeaker);
    SDL_Delay(10000);
    // 多线程停止
    playThread.join();
    recordThread.join();
    // sdlmic->stopSaveWav();
    sdlspeaker->stopPlayBack();
    sdlmic->stopRecording();

    SDL_Quit();
    return 0;
}
int main(int argc, char *args[])
{
    return main2();
}