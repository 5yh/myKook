#include "../../include/SDLMic.h"
SDLMic::SDLMic()
{
}

void SDLMic::showMicDevices()
{
    // 正式代码
    int numDevices = SDL_GetNumAudioDevices(true);
    std::cout << "麦克风设备数量：";
    micNumber = numDevices;
    std::cout << numDevices << std::endl;
    for (int i = 0; i < numDevices; ++i)
    {
        const char *deviceName = SDL_GetAudioDeviceName(i, true); // 获取第i个音频输入设备1的名称
        std::cout << i << ": " << deviceName << std::endl;
    }
}
void SDLMic::showMicDevice(int index)
{
    const char *deviceName = SDL_GetAudioDeviceName(index, true); // 获取第i个音频设备的名称
    std::cout << index << ": " << deviceName << std::endl;
}
void SDLMic::chooseMicDevice()
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
    micDeviceName = SDL_GetAudioDeviceName(micIndex, true);
    std::cout << "你选择的麦克风是" << this->micIndex << ": " << this->micDeviceName << std::endl;

    // showDevice(true, this->micIndex);
}

std::string SDLMic::getChosenDeviceName()
{
    return micDeviceName;
}
void SDLMic::setDesiredSpec(int sampleRate, int framesPerBuffer)
{
    this->desiredSpec.freq = sampleRate;         // 采样率
    this->desiredSpec.format = AUDIO_S16SYS;     // 音频格式
    this->desiredSpec.channels = 1;              // 声道数
    this->desiredSpec.samples = framesPerBuffer; // 缓冲区大小
    // this->desiredSpec.callback = audioCallback;  // 音频回调函数
    this->desiredSpec.callback = audioCallback2; // 音频回调函数
    this->desiredSpec.userdata = this;
}

void SDLMic::initAudioDevice()
{
    std::cout << "正在打开麦克风设备" << micDeviceName << std::endl;
    micDevice = SDL_OpenAudioDevice(micDeviceName.c_str(), true, &desiredSpec, &obtainedSpec, 0);
    if (micDevice == 0)
    {
        std::cerr << "打开麦克风失败！" << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}
void SDLMic::startRecording()
{
    if (micDevice != 0)
    {
        SDL_PauseAudioDevice(micDevice, 0);
        std::cout << "开始录制音频..." << std::endl;
    }
    else
    {
        std::cerr << "未选择麦克风设备或设备未初始化！" << std::endl;
    }
}

void SDLMic::stopRecording()
{
    if (micDevice != 0)
    {
        SDL_PauseAudioDevice(micDevice, 1);
        std::cout << "停止录制音频." << std::endl;
    }
    else
    {
        std::cerr << "未选择麦克风设备或设备未初始化！" << std::endl;
    }
}
void SDLMic::startSaveWav()
{
    audioFile.open("recorded_audio.wav", std::ios::binary);
    writeWavHeader(audioFile, desiredSpec.freq, desiredSpec.channels, 16); // 写入WAV文件头
}

void SDLMic::stopSaveWav()
{
    audioFile.close();
}
SDL_AudioDeviceID SDLMic::getMicID()
{
    return micDevice;
}
void SDLMic::setSpeaker(SDLSpeaker &speaker)
{
    this->speaker = &speaker;
}

// 留作备用 回调函数2
void SDLMic::audioCallback2(void *userdata, Uint8 *stream, int len)
{
    SDLMic *micInstance = static_cast<SDLMic *>(userdata);
    //  std::cout << SDL_GetQueuedAudioSize(micInstance->micDevice);
    if (micInstance != nullptr && micInstance->speaker != nullptr)
    {
        // 从麦克风获取音频数据
        // Uint8 *micData = new Uint8[len];
        // SDL_MixAudioFormat(micData, stream, micInstance->obtainedSpec.format, len, SDL_MIX_MAXVOLUME);
        // 将音频数据推送到输出缓冲区
        SDL_QueueAudio(micInstance->speaker->getSpeakerID(), stream, len);
        // std::cout << SDL_GetError();
        //  释放内存
        // delete[] micData;
    }
}

// 保存wav的回调
void SDLMic::audioCallback(void *userdata, Uint8 *stream, int len)
{
    // 将捕获到的音频数据发送到输出缓冲区
    // SDL_QueueAudio(1, stream, len);
    // std::cout << "回调函数haha" << std::endl;
    SDLMic *micInstance = static_cast<SDLMic *>(userdata);

    if (micInstance != nullptr)
    {
        micInstance->audioFile.write(reinterpret_cast<char *>(stream), len);
    }
}
// 给wav写头文件
void SDLMic::writeWavHeader(std::ofstream &file, int sampleRate, int numChannels, int bitsPerSample)
{
    // WAV 文件头部分
    const char *header = "RIFF";
    file.write(header, 4); // Chunk ID

    int fileSize = 0;                                   // Placeholder for file size
    file.write(reinterpret_cast<char *>(&fileSize), 4); // Placeholder for file size

    const char *format = "WAVE";
    file.write(format, 4); // Format

    const char *subchunk1ID = "fmt ";
    file.write(subchunk1ID, 4); // Subchunk1 ID

    int subchunk1Size = 16;
    file.write(reinterpret_cast<char *>(&subchunk1Size), 4); // Subchunk1 Size

    short audioFormat = 1;
    file.write(reinterpret_cast<char *>(&audioFormat), 2); // Audio Format

    short numChannelsShort = static_cast<short>(numChannels);
    file.write(reinterpret_cast<char *>(&numChannelsShort), 2); // Num Channels

    int sampleRateInt = sampleRate;
    file.write(reinterpret_cast<char *>(&sampleRateInt), 4); // Sample Rate

    int byteRate = sampleRate * numChannels * bitsPerSample / 8;
    file.write(reinterpret_cast<char *>(&byteRate), 4); // Byte Rate

    short blockAlign = numChannels * bitsPerSample / 8;
    file.write(reinterpret_cast<char *>(&blockAlign), 2); // Block Align

    short bitsPerSampleShort = static_cast<short>(bitsPerSample);
    file.write(reinterpret_cast<char *>(&bitsPerSampleShort), 2); // Bits Per Sample

    const char *subchunk2ID = "data";
    file.write(subchunk2ID, 4); // Subchunk2 ID

    int dataSize = 0;                                   // Placeholder for data size
    file.write(reinterpret_cast<char *>(&dataSize), 4); // Placeholder for data size

    // Move the file pointer to the beginning of data
    file.seekp(4, std::ios::beg);
    int actualFileSize = static_cast<int>(file.tellp()) - 8;

    file.write(reinterpret_cast<char *>(&actualFileSize), 4); // Write actual file size

    // Move the file pointer to the beginning of data size
    file.seekp(40, std::ios::beg);
}
