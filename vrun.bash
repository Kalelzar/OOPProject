#!/bin/bash

./build.bash && valgrind -s --show-leak-kinds=all --leak-check=full cmake-build-debug/OOPProject_run
