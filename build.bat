conan install . --profile=conan_profile_win64_debug  --output-folder=build-debug --build=missing --remote=conancenter
cd build-debug
cmake .. -G "Visual Studio 17 2022" -DZFG_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"