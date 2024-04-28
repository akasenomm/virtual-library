cmake_minimum_required(VERSION 3.27)
project(virtual_library)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(virtual_library
        main.cpp
        application.h
        Library.h
        Library.cpp
        Book.cpp
        Book.h
        Library.cpp
        user.h
        application.cpp
        user.cpp
)