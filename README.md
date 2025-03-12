[中文版本](READMECN.md)

# myKook

## Introduction

This is an audio recording and playback project based on SDL2 and ASIO, including client and server sides. The client is responsible for recording audio and sending it to the server over the network, and the server receives and plays the audio.

## Directory Structure

```
.gitignore
client/
    .gitignore
    build_release.bat
    build.bat
    CMakeLists.txt
    conan_profile_win64_debug
    conan_profile_win64_release
    conanfile.py
    include/
        SDLMic.h
        SDLSpeaker.h
    src/
        audio/
            SDLAudio.cpp
            SDLMic.cpp
            SDLSpeaker.cpp
        main.cpp
        net/
            netTest.cpp
remark.txt
server/
    build_release.bat
    build.bat
    CMakeLists.txt
    conan_profile_win64_debug
    conan_profile_win64_release
    conanfile.py
    src/
        main.cpp
```

## Requirements

- Windows
- Visual Studio 2022
- Conan
- CMake 3.28 or higher

## Install Dependencies

### Client

1. Navigate to the [`client`](client) directory:
    ```sh
    cd client
    ```

2. Install dependencies:
    ```sh
    conan install . --profile="conan_profile_win64_debug" --output-folder=build-debug --build=missing --remote=conancenter
    ```

### Server

1. Navigate to the [`server`](server) directory:
    ```sh
    cd server
    ```

2. Install dependencies:
    ```sh
    conan install . --profile="conan_profile_win64_debug" --output-folder=build-debug --build=missing --remote=conancenter
    ```

## Build Project

### Client

1. Navigate to the [`client`](client) directory:
    ```sh
    cd client
    ```

2. Run the build script:
    ```sh
    build.bat
    ```

### Server

1. Navigate to the [`server`](server) directory:
    ```sh
    cd server
    ```

2. Run the build script:
    ```sh
    build.bat
    ```

## Run Project

### Client

1. Navigate to the [`client/build-debug`](client/build-debug) directory:
    ```sh
    cd client/build-debug
    ```

2. Run the executable:
    ```sh
    myKook-client.exe
    ```

### Server

1. Navigate to the [`server/build-debug`](server/build-debug) directory:
    ```sh
    cd server/build-debug
    ```

2. Run the executable:
    ```sh
    myKook-server.exe
    ```

## Project Features

- **Audio Recording and Playback**: Uses the SDL2 library to manage audio devices, record, and play audio.
- **Network Communication**: Uses the ASIO library to transmit audio data between the client and server.
- **Multithreading**: Supports multithreading to ensure real-time audio recording and playback.

## License

This project uses the Boost Software License, Version 1.0. For more details, see [LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt).