cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

# Source
project(OOPProject VERSION 0.0.1)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS
        "src/cpp/src/*.hpp"
        "src/cpp/src/*.cpp"
        )

add_executable(OOPProject_run src/cpp/main.cpp ${ALL_SRC})


add_subdirectory(src/cpp/src)
