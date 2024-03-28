#include <SDL.h>
#include <iostream>
#include <locale.h>
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
    // 正式代码
    //0是喇叭，1是扬声器
    int numDevices = SDL_GetNumAudioDevices(1);
    std::cout << "numDevices:" << numDevices << std::endl;
    for (int i = 0; i < numDevices; ++i)
    {
        const char *deviceName = SDL_GetAudioDeviceName(i, 1); // 获取第i个音频输入设备1的名称
        std::cout << i << ": " << deviceName << std::endl;
    }
    SDL_Quit();
    return 0;
}