#include <SDL.h>
#include <iostream>
#include <locale.h>
#include "audio/SDLAudio.cpp"
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
    // SDLAudio *sdlaudio = new SDLAudio();
    // sdlaudio->showDevices(true);
    // sdlaudio->chooseMicDevice();
    // sdlaudio->showDevices(false);
    // sdlaudio->chooseSpeakerDevice();
    // sdlaudio->setDesiredSpec();
    // // std::cout<<sdlaudio->getChosenDeviceName(true);
    // // std::cout << sdlaudio->getChosenDeviceName(false);
    // sdlaudio->initAudioDevice(true);
    // sdlaudio->startRecording();
    // SDL_Delay(3000);
    // sdlaudio->stopRecording();
    SDLMic *sdlmic = new SDLMic();
    sdlmic->showMicDevices();
    sdlmic->showMicDevice(0);
    sdlmic->chooseMicDevice();
    sdlmic->setDesiredSpec();
    sdlmic->initAudioDevice();
    sdlmic->startRecording();
    SDL_Delay(3000);
    sdlmic->stopRecording();
    SDL_Quit();
    return 0;
}