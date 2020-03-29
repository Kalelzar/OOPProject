#!/bin/bash

./build.bash && valgrind -s --leak-check=full cmake-build-debug/OOPProject_run
