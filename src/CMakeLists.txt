cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(ThisFunc VERSION 0.0.1)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS
        "*.cpp"
        )



add_library(ThisFunc SHARED ${ALL_SRC})
set_target_properties(ThisFunc PROPERTIES LINKER_LANGUAGE CXX)
