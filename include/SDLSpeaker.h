#pragma once
#pragma execution_character_set("utf-8")

#include <SDL.h>
#include <iostream>
#include <string>

class SDLMic;

class SDLSpeaker
{
public:
    SDLSpeaker();
    void showSpeakerDevices();
    void showSpeakerDevice(int index);
    void chooseSpeakerDevice();
    std::string getChosenDeviceName();
    void setDesiredSpec(int sampleRate = 44100, int framesPerBuffer = 512);
    void initAudioDevice();
    void startPlayBack();
    void stopPlayBack();
    void setMic(SDLMic &mic);
    SDL_AudioDeviceID getSpeakerID();

private:
    int speakerNumber;
    int speakerIndex;
    std::string speakerDeviceName;
    SDL_AudioSpec desiredSpec, obtainedSpec;
    SDL_AudioDeviceID speakerDevice;
    SDLMic *mic = nullptr;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
};
