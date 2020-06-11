#!/bin/bash

./build.bash && valgrind -s --leak-check=full --track-origins=yes cmake-build-debug/src/cpp/test/OOPProject_tests_run
