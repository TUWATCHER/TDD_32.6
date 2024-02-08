cmake_minimum_required(VERSION 3.20.0)
project("tdd")

enable_testing()
add_subdirectory(googletest)

add_executable(tdd main.cpp)
target_link_libraries(tdd gtest_main gmock_main)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
