#include <SDL.h>
#include <iostream>
#include <locale.h>
#include "audio/SDLSpeaker.cpp"
#include "audio/SDLMic.cpp"

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
     //sdlmic->showMicDevice(0);
    sdlmic->chooseMicDevice();
    sdlmic->setDesiredSpec();
    sdlmic->initAudioDevice();
    sdlmic->startRecording();
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
    //sdlspeaker->initplay();
    sdlspeaker->startPlayBack();
    //while (1) {
    //    sdlspeaker->playSound();
    //}

    SDL_Delay(400000);
    // sdlmic->stopSaveWav();
    sdlspeaker->stopPlayBack();
    sdlmic->stopRecording();

    SDL_Quit();
    return 0;
}