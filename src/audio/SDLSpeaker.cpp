﻿#pragma execution_character_set("utf-8")
#include <SDL.h>
#include <string>
class SDLSpeaker
{
public:
    SDLSpeaker()
    {
    }

    void showSpeakerDevices()
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
    void showSpeakerDevice(int index)
    {
        const char *deviceName = SDL_GetAudioDeviceName(index, false); // 获取第i个音频设备的名称
        std::cout << index << ": " << deviceName << std::endl;
    }
    void chooseSpeakerDevice()
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

    std::string getChosenDeviceName()
    {
        return speakerDeviceName;
    }
    void setDesiredSpec(int sampleRate = 44100, int framesPerBuffer = 512)
    {
        this->desiredSpec.freq = sampleRate;         // 采样率
        this->desiredSpec.format = AUDIO_S16SYS;     // 音频格式
        this->desiredSpec.channels = 1;              // 声道数
        this->desiredSpec.samples = framesPerBuffer; // 缓冲区大小
        this->desiredSpec.callback = audioCallback;  // 音频回调函数
        this->desiredSpec.userdata = this;
    }

    void initAudioDevice()
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
    void startPlayBack()
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
    void stopPlayBack()
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
    void setMic(SDLMic &mic)
    {
        this->mic = mic;
    }

private:
    // 扬声器数量
    int speakerNumber;
    // 扬声器编号
    int speakerIndex;
    // const char * to string
    std::string speakerDeviceName;
    // sdl你想给的参数和实际使用的参数
    SDL_AudioSpec desiredSpec, obtainedSpec;
    // 扬声器设备
    SDL_AudioDeviceID speakerDevice;
    // 麦克风设备的引用
    SDLMic &mic;
    static void audioCallback(void *userdata, Uint8 *stream, int len)
    {
        // 将捕获到的音频数据发送到输出缓冲区
        // SDL_QueueAudio(1, stream, len);
        std::cout << "回调函数haha" << std::endl;
        // SDLSpeaker *speakerInstance = static_cast<SDLSpeaker *>(userdata);
        // if (speakerInstance != nullptr)
        // {
        //     SDLMic& mic = speakerInstance->mic;
        //     if (mic.micDevice != 0)
        //     {
        //         SDL_memset(stream, 0, len);
        //         SDL_DequeueAudio(mic.micDevice, stream, len);
        //     }
        // }
    }
};