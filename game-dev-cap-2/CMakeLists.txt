cmake_minimum_required(VERSION 3.22)
project(game_dev_cap_2)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C:/Users/cosmi/Desktop/C++/lib/SDL2-2.26.0/include)
set(SDL2_LIB_DIR C:/Users/cosmi/Desktop/C++/lib/SDL2-2.26.0/lib/x64)


#set(SDL2_INCLUDE_DIR C:/Users/Cosmin/Desktop/C++/lib/SDL2-2.26.0/include)
#set(SDL2_LIB_DIR C:/Users/Cosmin/Desktop/C++/lib/SDL2-2.26.0/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(game_dev_cap_2 main.cpp Actor.cpp Actor.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

