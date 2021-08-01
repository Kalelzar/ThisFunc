cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)

project(ThisFunc VERSION 0.0.1)

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo;Debug" CACHE STRING "Build type selections" FORCE)

include(CTest)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

add_executable(ThisFunc_main exec/main.cpp)
add_executable(tfl exec/tooling/tfl.cpp)
target_link_libraries(ThisFunc_main PUBLIC ThisFunc)
target_link_libraries(tfl PUBLIC ThisFunc)

add_subdirectory(test)
add_subdirectory(bench)
