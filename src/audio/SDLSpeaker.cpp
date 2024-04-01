#pragma execution_character_set("utf-8")
#include <SDL.h>
#include <string>
class SDLMic;
class SDLSpeaker
{
public:
    SDLSpeaker()
    {
    }
    //////////////////////////////////////////////////////////////////////////////
    Uint8 *audio_buffer=nullptr;
    Uint32 audio_length=0;
    void initplay()
    {
        audio_length = obtainedSpec.freq * obtainedSpec.channels * sizeof(Sint16);
        audio_buffer = new Uint8[audio_length];
    }

    void generateTone(double frequency)
    {
        Uint16 *samples = reinterpret_cast<Uint16 *>(audio_buffer);
        int i;

        for (i = 0; i < audio_length / 2; i++)
        {
            double t = static_cast<double>(i) / obtainedSpec.freq;
            samples[i] = static_cast<Uint16>(32767.0 * 0.5 * sin(2 * M_PI * frequency * t));
            //std::cout << samples[i] << std::endl;
        }
    }

    void playSound(double frequency = 261.63)
    {
        generateTone(frequency);
        SDL_QueueAudio(speakerDevice, audio_buffer, audio_length);
        //std::cout << SDL_GetError();
        SDL_PauseAudio(0);
    }
    /////////////////////////////////////////////////////////////////
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
        this->desiredSpec.callback = nullptr;  // 音频回调函数
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
        this->mic = &mic;
    }
    SDL_AudioDeviceID getSpeakerID()
    {
        return speakerDevice;
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
    // 麦克风设备的指针
    SDLMic *mic = nullptr;
    static void audioCallback(void *userdata, Uint8 *stream, int len)
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
        // std::cout << "当前扬声器播放声音的大小：" << amplitude << std::endl;

        // // 将捕获到的音频数据发送到输出缓冲区
        // // SDL_QueueAudio(1, stream, len);
        // std::cout << "回调函数haha" << std::endl;
        SDLSpeaker *speakerInstance = static_cast<SDLSpeaker *>(userdata);
        // std::cout << SDL_GetQueuedAudioSize(speakerInstance->speakerDevice);
        if (speakerInstance != nullptr && speakerInstance->mic != nullptr)
        {
            // std::cout << "回调函数haha" << std::endl;
            // std::cout << speakerInstance->mic->getBufferSize();
            // SDL_AudioDeviceID micDevice = speakerInstance->mic->getMicID();
            // int bufferSize = mic->getBufferSize();

            //     // 从麦克风获取音频数据
            // Uint8* micData = new Uint8[len];
            //     speakerInstance->mic->getMicData(micData, len);

            //     // 将音频数据推送到输出缓冲区
            //     SDL_QueueAudio(speakerInstance->speakerDevice, micData, len);

            //     // 释放内存
            //     delete[] micData;
        }
    }
};