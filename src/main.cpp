#include <SDL.h>
#include <iostream>
#include <locale.h>

#include "audio/SDLMic.cpp"
#include "audio/SDLSpeaker.cpp"
int main(int argc, char *args[])
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
    sdlmic->showMicDevice(0);
    sdlmic->chooseMicDevice();
    sdlmic->setDesiredSpec();
    sdlmic->initAudioDevice();
    sdlmic->startRecording();
    sdlmic->startSaveWav();
    SDL_Delay(4000);
    sdlmic->stopSaveWav();
    sdlmic->stopRecording();
    std::cout << "---------------------------------------------------" << std::endl;
    // SDLSpeaker *sdlspeaker = new SDLSpeaker();
    // sdlspeaker->showSpeakerDevices();
    // sdlspeaker->showSpeakerDevice(0);
    // sdlspeaker->chooseSpeakerDevice();
    // sdlspeaker->setDesiredSpec();


    SDL_Quit();
    return 0;
}