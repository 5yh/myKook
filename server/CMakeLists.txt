cmake_minimum_required(VERSION 3.28)

project(myKook-server CXX)

set(CMAKE_CXX_STANDARD 20)

# find_package(SDL2 CONFIG REQUIRED)
# find_package(OpenSSL REQUIRED)
# find_package(asio REQUIRED CONFIG)
find_package(Boost REQUIRED)
# find_package(nlohmann_json REQUIRED CONFIG)
# find_package(websocketpp REQUIRED)
file(GLOB_RECURSE HEADER_FILES include/*.h) 
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/audio/*.cpp src/net/*.cpp)
# include_directories(${HEADER_FILES})
# message("Nihao")
# add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
# if(TARGET SDL2::SDL2-static)
#     target_link_libraries(${PROJECT_NAME} SDL2::SDL2-static)
# else()
#     message("nihao")
#     target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
# endif()
# target_link_libraries(${PROJECT_NAME} websocketpp::websocketpp)
# target_link_libraries(${PROJECT_NAME} openssl::openssl)
# target_link_libraries(${PROJECT_NAME} asio::asio)
target_link_libraries(${PROJECT_NAME} boost::boost)
# target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
# add_subdirectory(src/audio)



