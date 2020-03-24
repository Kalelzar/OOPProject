cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

project(OOPProject_tests)


add_subdirectory(${CMAKE_HOME_DIRECTORY}/lib/googletest ${CMAKE_HOME_DIRECTORY}/googletest-build)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(OOPProject_tests_run DateTests.cpp Date.cpp)
target_link_libraries(OOPProject_tests_run gtest gtest_main)