#pragma once
#pragma execution_character_set("utf-8")
#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>
#include "SDLSpeaker.h" // Assuming the header file is in the same directory
#include "../src/net/netTest.cpp"
#include <asio.hpp>
class SDLMic
{
public:
    SDLMic();

    void showMicDevices();
    void showMicDevice(int index);
    void chooseMicDevice();
    std::string getChosenDeviceName();
    void setDesiredSpec(int sampleRate = 44100, int framesPerBuffer = 512);
    void initAudioDevice();
    void startRecording();
    void stopRecording();
    void startSaveWav();
    void stopSaveWav();
    SDL_AudioDeviceID getMicID();
    void setSpeaker(SDLSpeaker &speaker);
    void setClient(Client &client);

private:
    int micNumber;
    int micIndex;
    std::string micDeviceName;
    SDL_AudioSpec desiredSpec, obtainedSpec;
    SDL_AudioDeviceID micDevice;
    SDLSpeaker *speaker;
    std::ofstream audioFile;
    // client的引用
    Client *client;
    static void audioCallback3(void *userdata, Uint8 *stream, int len);
    static void audioCallback2(void *userdata, Uint8 *stream, int len);
    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void writeWavHeader(std::ofstream &file, int sampleRate, int numChannels, int bitsPerSample);
};
