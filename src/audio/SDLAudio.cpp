#pragma execution_character_set("utf-8")
#include <SDL.h>
class SDLAudio
{
public:
    SDLAudio()
    {
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
    void chooseMicDevice()
    {
        while (true)
        {
            std::cout << "请输入麦克风设备索引:" << std::endl;
            int micIndex;
            std::cin >> micIndex;
            if (micIndex >= 0 && micIndex < micNumber)
            {
                this->micIndex = micIndex;
                std::cout << "选择了" <<this->micIndex<<"号麦克风"<< std::endl;
                break;
            }
            else
            {
                std::cout << "麦克风索引输入错误，请重新输入。" << std::endl;
            }
        }
    }

private:
    // 扬声器和麦克风数量
    int speakerNumber;
    int micNumber;
    // 扬声器和麦克风编号
    int speakerIndex;
    int micIndex;
};