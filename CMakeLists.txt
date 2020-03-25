cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

# Source
project(OOPProject VERSION 0.0.1)

add_executable(OOPProject_run src/cpp/src/main.cpp src/cpp/src/File.cpp src/cpp/src/Date.cpp src/cpp/src/CommandScanner.cpp src/cpp/src/CommandInterpreter.cpp src/cpp/src/HotelState.cpp src/cpp/src/Room.cpp src/cpp/src/RoomList.cpp )


add_subdirectory(src/cpp/src)