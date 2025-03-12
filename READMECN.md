# myKook

## 简介

这是一个基于SDL2和ASIO的音频录制和播放项目，包含客户端和服务器端。客户端负责录制音频并通过网络发送到服务器，服务器接收音频并播放。

## 目录结构

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

## 环境要求

- Windows
- Visual Studio 2022
- Conan
- CMake 3.28或更高版本

## 安装依赖

### 客户端

1. 进入[`client`](client)目录：
    ```sh
    cd client
    ```

2. 安装依赖：
    ```sh
    conan install . --profile="conan_profile_win64_debug" --output-folder=build-debug --build=missing --remote=conancenter
    ```

### 服务器

1. 进入[`server`](server)目录：
    ```sh
    cd server
    ```

2. 安装依赖：
    ```sh
    conan install . --profile="conan_profile_win64_debug" --output-folder=build-debug --build=missing --remote=conancenter
    ```

## 构建项目

### 客户端

1. 进入[`client`](client)目录：
    ```sh
    cd client
    ```

2. 运行构建脚本：
    ```sh
    build.bat
    ```

### 服务器

1. 进入[`server`](server)目录：
    ```sh
    cd server
    ```

2. 运行构建脚本：
    ```sh
    build.bat
    ```

## 运行项目

### 客户端

1. 进入[`client/build-debug`](client/build-debug)目录：
    ```sh
    cd client/build-debug
    ```

2. 运行可执行文件：
    ```sh
    myKook-client.exe
    ```

### 服务器

1. 进入[`server/build-debug`](server/build-debug)目录：
    ```sh
    cd server/build-debug
    ```

2. 运行可执行文件：
    ```sh
    myKook-server.exe
    ```

## 项目特色

- **音频录制与播放**：使用SDL2库实现音频设备的管理、录制和播放功能。
- **网络通信**：使用ASIO库实现客户端和服务器之间的音频数据传输。
- **多线程**：支持多线程操作，确保音频录制和播放的实时性。

## 许可证

此项目使用Boost软件许可证，版本1.0。详细信息请参见[LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)。