cmake_minimum_required(VERSION 3.28)
project(myKook CXX)

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
if(TARGET SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2-static)
else()
    message("nihao")
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
endif()




