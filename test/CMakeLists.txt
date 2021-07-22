cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
        "*.cpp"
        )

add_executable(ThisFunc_test ${TEST_SRC})
target_link_libraries(ThisFunc_test PUBLIC gtest_main rapidcheck rapidcheck_gtest ThisFunc)
