#include <SDL.h>
#include <iostream>
#include <locale.h>
#include "../include/SDLSpeaker.h"
#include "../include/SDLMic.h"
#include <thread>
#include <asio.hpp>
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
    auto &&service = asio::io_service{};
    (void)service;
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
    return main1();
}