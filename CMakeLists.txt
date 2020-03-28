cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

# Source
project(OOPProject VERSION 0.0.1)

add_executable(OOPProject_run src/cpp/src/main.cpp src/cpp/src/File.cpp src/cpp/src/Date.cpp src/cpp/src/CommandScanner.cpp src/cpp/src/CommandInterpreter.cpp src/cpp/src/HotelState.cpp src/cpp/src/Room.cpp src/cpp/src/ArrayList.hpp src/cpp/src/ArraySet.hpp src/cpp/src/IList.hpp src/cpp/src/LinkedList.hpp src/cpp/src/HashMap.hpp src/cpp/src/BinaryTree.hpp)


add_subdirectory(src/cpp/src)
