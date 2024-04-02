#include "../../include/SDLSpeaker.h"
SDLSpeaker::SDLSpeaker() : speakerNumber(0), speakerIndex(0), speakerDeviceName(""), mic(nullptr)
{
}
void SDLSpeaker::showSpeakerDevices()
{
    // 正式代码
    int numDevices = SDL_GetNumAudioDevices(false);
    std::cout << "扬声器设备数量：";
    speakerNumber = numDevices;
    std::cout << numDevices << std::endl;
    for (int i = 0; i < numDevices; ++i)
    {
        const char *deviceName = SDL_GetAudioDeviceName(i, false); // 获取第i个音频输入设备1的名称
        std::cout << i << ": " << deviceName << std::endl;
    }
}
void SDLSpeaker::showSpeakerDevice(int index)
{
    const char *deviceName = SDL_GetAudioDeviceName(index, false); // 获取第i个音频设备的名称
    std::cout << index << ": " << deviceName << std::endl;
}
void SDLSpeaker::chooseSpeakerDevice()
{
    if (speakerNumber == 0)
    {
        std::cout << "无可用扬声器用于选择！" << std::endl;
        return;
    }
    do
    {
        std::cout << "请输入一个扬声器的索引（0 到 " << speakerNumber - 1 << "）：";
        while (!(std::cin >> this->speakerIndex) || this->speakerIndex < 0 || this->speakerIndex >= speakerNumber)
        {
            std::cout << "输入无效，请重新输入一个有效的扬声器索引（0 到 " << speakerNumber - 1 << "）：";
            std::cin.clear();                                                   // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区
        }
    } while (this->speakerIndex < 0 || this->speakerIndex >= speakerNumber);
    speakerDeviceName = SDL_GetAudioDeviceName(speakerIndex, false);
    std::cout << "你选择的扬声器是" << this->speakerIndex << ": " << this->speakerDeviceName << std::endl;
}

std::string SDLSpeaker::getChosenDeviceName()
{
    return speakerDeviceName;
}
void SDLSpeaker::setDesiredSpec(int sampleRate, int framesPerBuffer)
{
    this->desiredSpec.freq = sampleRate;         // 采样率
    this->desiredSpec.format = AUDIO_S16SYS;     // 音频格式
    this->desiredSpec.channels = 1;              // 声道数
    this->desiredSpec.samples = framesPerBuffer; // 缓冲区大小
    this->desiredSpec.callback = nullptr;        // 音频回调函数
    this->desiredSpec.userdata = this;
}

void SDLSpeaker::initAudioDevice()
{
    std::cout << "正在打开扬声器设备" << speakerDeviceName << std::endl;
    speakerDevice = SDL_OpenAudioDevice(speakerDeviceName.c_str(), false, &desiredSpec, &obtainedSpec, 0);
    if (speakerDevice == 0)
    {
        std::cerr << "打开扬声器失败！" << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}
void SDLSpeaker::startPlayBack()
{
    if (speakerDevice != 0)
    {
        SDL_PauseAudioDevice(speakerDevice, 0);
        std::cout << "开始播放录制的音频..." << std::endl;
    }
    else
    {
        std::cerr << "未选择扬声器设备或设备未初始化！" << std::endl;
    }
}
void SDLSpeaker::stopPlayBack()
{
    if (speakerDevice != 0)
    {
        SDL_PauseAudioDevice(speakerDevice, 1);
        std::cout << "停止播放录制的音频." << std::endl;
    }
    else
    {
        std::cerr << "未选择扬声器设备或设备未初始化！" << std::endl;
    }
}
// 有问题 编译没过
void SDLSpeaker::setMic(SDLMic &mic)
{
    this->mic = &mic;
}
SDL_AudioDeviceID SDLSpeaker::getSpeakerID()
{
    return speakerDevice;
}

void SDLSpeaker::audioCallback(void *userdata, Uint8 *stream, int len)
{
    // std::cout << len;
    int amplitude = 0;
    for (int i = 0; i < len; ++i)
    {
        Uint8 sample = stream[i];
        // 计算每个采样的振幅
        amplitude += abs(sample - 128); // 假设音频格式是 8-bit signed
    }

    // 计算平均振幅
    amplitude /= len;

    // 显示振幅
    std::cout << "当前扬声器播放声音的大小：" << amplitude << std::endl;
    SDLSpeaker *speakerInstance = static_cast<SDLSpeaker *>(userdata);
    if (speakerInstance != nullptr && speakerInstance->mic != nullptr)
    {
    }
}
