cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
include(GoogleTest)

file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
        "*.cpp"
        )

add_executable(ThisFunc_test ${TEST_SRC})
target_link_libraries(ThisFunc_test PUBLIC rapidcheck gtest gtest_main ThisFunc)

gtest_discover_tests(ThisFunc_test)
