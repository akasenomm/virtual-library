cmake_minimum_required(VERSION 3.27)
project(virtual_library)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(virtual_library
        src/main.cpp
        include/application.h
        include/Library.h
        src/Library.cpp
        src/Book.cpp
        include/Book.h
        include/user.h
        src/application.cpp
        src/user.cpp
        src/sqlite3.c  # Add sqlite3.c to your sources
)