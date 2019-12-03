cmake_minimum_required(VERSION 3.16)
project(PrettyTable)
set(CMAKE_CXX_STANDARD 14)

add_executable(PrettyTable test.cpp
            PrettyTable.cpp PrettyTable.h
            myTermColor.cpp myTermColor.h
            Sign.h)
