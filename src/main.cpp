#include <SDL.h>
#include <iostream>
#include <locale.h>
#include "../include/SDLSpeaker.h"
#include "../include/SDLMic.h"
#include <thread>
#include "net\netTest.cpp"
#include <chrono>
using asio::ip::tcp;
void recordWithMic(SDLMic *sdlmic)
{
    sdlmic->startRecording();
}

void playWithSpeaker(SDLSpeaker *sdlspeaker)
{
    sdlspeaker->startPlayBack();
}
int main4()
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

    std::cout << "---------------------------------------------------" << std::endl;
    SDLSpeaker *sdlspeaker = new SDLSpeaker();
    sdlspeaker->showSpeakerDevices();
    sdlspeaker->chooseSpeakerDevice();
    sdlspeaker->setDesiredSpec();
    sdlspeaker->initAudioDevice();
    sdlspeaker->startPlayBack();
    try
    {
        asio::io_context io_context;
        std::cout << "start server thread\n";
        Server server(io_context, 18080, sdlspeaker);
        io_context.run();

        SDL_Delay(100000);
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    SDL_Quit();
    return 0;
    // try
    // {
    //     asio::io_context io_context;

    //     std::thread server_thread([&io_context, &sdlspeaker]()
    //                               {
    //                                 std::cout<<"start server thread\n";
    //         Server server(io_context, 8080);
    //         io_context.run();
    //         sdlspeaker->startPlayBack(); });
    //     SDL_Delay(100000);
    //     server_thread.join();
    // }
    // catch (std::exception &e)
    // {
    //     std::cerr << "Exception: " << e.what() << std::endl;
    // }

    // 多线程停止
}
int main3()
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
    sdlmic->chooseMicDevice();
    sdlmic->setDesiredSpec();
    sdlmic->initAudioDevice();
    try
    {
        asio::io_context io_context;
        std::cout << "start client thread\n";
        Client client(io_context, "home.1114514.xyz", "18080");
        sdlmic->setClient(client);
        sdlmic->startRecording();
        SDL_Delay(100000);
        std::cout << "111";
    }
    catch (std::exception &e)
    {
        std::cerr << "myException: " << e.what() << std::endl;
    }
    sdlmic->stopRecording();

    // SDL_Quit();
    return 0;

    // try
    // {
    //     asio::io_context io_context;
    //     std::thread client_thread([&io_context, &sdlmic]()
    //                               {
    //                                   std::cout << "start client thread\n";
    //                                   Client client(io_context, "127.0.0.1", "8080");
    //                                   sdlmic->setClient(client);
    //                                   sdlmic->startRecording(); });
    //     SDL_Delay(20000);
    //     std::cout << "111";
    //     client_thread.join();
    // }
    // catch (std::exception &e)
    // {
    //     std::cerr << "myException: " << e.what() << std::endl;
    // }
    // 多线程
    // std::thread recordThread(recordWithMic, sdlmic);
    // std::thread playThread(playWithSpeaker, sdlspeaker);

    // 多线程停止
    // recordThread.join();
    // sdlmic->stopSaveWav();
}
// int main2()
// {
//     // Server
//     try
//     {
//         asio::io_context io_context;

//         std::thread server_thread([&io_context]()
//                                   {
//                                     std::cout<<"start server thread\n";
//             Server server(io_context, 8080);
//             io_context.run(); });
//         std::thread client_thread([&io_context]()
//                                   {
//                                       std::cout << "start client thread\n";
//                                       Client client(io_context, "127.0.0.1", "8080");

//                                       Uint8 data[stream_length];  // 假设有要发送的数据
//                                       int length = stream_length; // 假设数据长度为 stream_length
//                                       while (1)
//                                       {
//                                           client.send_data(data, length);
//                                           std::this_thread::sleep_for(std::chrono::seconds(1));
//                                       }

//                                       //   std::cout<<"client after send\n";
//                                   });
//         server_thread.join();
//         client_thread.join();
//     }
//     catch (std::exception &e)
//     {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }
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
    // return main1();
    // return main2();
    // std::thread thread1(main4);
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    std::thread thread2(main3);

    // thread1.join();
    thread2.join();
    // // main1();
    return 0;
}