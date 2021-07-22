cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(ThisFunc VERSION 0.0.1)

add_subdirectory(ThisFunc)

add_executable(ThisFunc_main exec/main.cpp)
target_link_libraries(ThisFunc_main PUBLIC ThisFunc)

add_subdirectory(test)
