#include <SDL.h>
#include <iostream>
#include <locale.h>
#include "audio/SDLAudio.cpp"
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
    SDLAudio *sdlaudio = new SDLAudio();
    sdlaudio->showDevices(true);
    sdlaudio->chooseMicDevice();
    sdlaudio->showDevices(false);

    SDL_Quit();
    return 0;
}