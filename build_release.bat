conan install . --profile="conan_profile_win64_release"  --output-folder=build-release --build=missing --remote=conancenter
cd build-release
cmake .. -G "Visual Studio 17 2022" -DZFG_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"