cmake_minimum_required(VERSION 3.21)
project(learn_SDL)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C:/Users/cosmi/Desktop/C++/lib/SDL2-2.26.0/include)
set(SDL2_LIB_DIR C:/Users/cosmi/Desktop/C++/lib/SDL2-2.26.0/lib/x64)


#set(SDL2_INCLUDE_DIR C:/Users/Cosmin/Desktop/C++/lib/SDL2-2.26.0/include)
#set(SDL2_LIB_DIR C:/Users/Cosmin/Desktop/C++/lib/SDL2-2.26.0/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


add_executable(learn_SDL main.cpp Game.cpp Game.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
