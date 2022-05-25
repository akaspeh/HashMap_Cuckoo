cmake_minimum_required(VERSION 3.20)
project(HashMap_Cuckoo)

set(CMAKE_CXX_STANDARD 23)

add_executable(HashMap_Cuckoo main.cpp HashMap.h DynamicArr.h)
