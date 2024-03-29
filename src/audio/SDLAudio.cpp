#pragma execution_character_set("utf-8")
#include <SDL.h>
class SDLAudio
{
public:
    SDLAudio()
    {
    }
    static void audioCallback(void *userdata, Uint8 *stream, int len)
    {
        // 将捕获到的音频数据发送到输出缓冲区
        SDL_QueueAudio(1, stream, len);
    }
    void showDevices(bool isMic)
    {
        // 正式代码
        // 0是喇叭，1是扬声器
        int numDevices = SDL_GetNumAudioDevices(isMic);
        if (isMic)
        {
            std::cout << "麦克风设备数量：";
            micNumber = numDevices;
        }
        else
        {
            std::cout << "扬声器设备数量：";
            speakerNumber = numDevices;
        }
        std::cout << numDevices << std::endl;
        for (int i = 0; i < numDevices; ++i)
        {
            const char *deviceName = SDL_GetAudioDeviceName(i, isMic); // 获取第i个音频输入设备1的名称
            std::cout << i << ": " << deviceName << std::endl;
        }
    }
    void showDevice(bool isMic, int index)
    {
        const char *deviceName = SDL_GetAudioDeviceName(index, isMic); // 获取第i个音频设备的名称
        std::cout << index << ": " << deviceName << std::endl;
    }
    void chooseMicDevice()
    {
        if (micNumber == 0)
        {
            std::cout << "无可用麦克风用于选择！" << std::endl;
            return;
        }
        do
        {
            std::cout << "请输入一个麦克风的索引（0 到 " << micNumber - 1 << "）：";
            while (!(std::cin >> this->micIndex) || this->micIndex < 0 || this->micIndex >= micNumber)
            {
                std::cout << "输入无效，请重新输入一个有效的麦克风索引（0 到 " << micNumber - 1 << "）：";
                std::cin.clear();                                                   // 清除错误标志
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区
            }
        } while (this->micIndex < 0 || this->micIndex >= micNumber);
        std::cout << "你选择的麦克风索引是：" << this->micIndex << std::endl;
        showDevice(true, this->micIndex);
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
        std::cout << "你选择的扬声器索引是：" << this->speakerIndex << std::endl;
        showDevice(false, this->speakerIndex);
    }
    void setDesiredSpec(int sampleRate = 44100, int framesPerBuffer = 512)
    {
        this->desiredSpec.freq = sampleRate;         // 采样率
        this->desiredSpec.format = AUDIO_S16SYS;     // 音频格式
        this->desiredSpec.channels = 1;              // 声道数
        this->desiredSpec.samples = framesPerBuffer; // 缓冲区大小
        this->desiredSpec.callback = audioCallback;  // 音频回调函数
        this->desiredSpec.userdata = NULL;
    }

private:
    // 扬声器和麦克风数量
    int speakerNumber;
    int micNumber;
    // 扬声器和麦克风编号
    int speakerIndex;
    int micIndex;
    // sdl你想给的参数和实际使用的参数
    SDL_AudioSpec desiredSpec, obtainedSpec;
};