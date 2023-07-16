cmake_minimum_required(VERSION 3.26)
project(untitled6)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled6 main.cpp AES.cpp AES.h SHA256.cpp SHA256.h list.cpp list.h node.cpp node.h encrypt_api.cpp encrypt_api.h)
