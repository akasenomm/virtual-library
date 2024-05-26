cmake_minimum_required(VERSION 3.27)
project(virtual_library)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(virtual_library
        src/main.cpp
        include/Application.h
        include/Library.h
        src/library.cpp
        src/book.cpp
        include/Book.h
        include/User.h
        src/application.cpp
        src/user.cpp
        src/sqlite3.c  # Add sqlite3.c to your sources
)