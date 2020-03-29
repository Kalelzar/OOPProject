#!/bin/bash

./build.bash && valgrind -s --leak-check=full cmake-build-debug/src/cpp/src/OOPProject_tests_run
