cmake_minimum_required(VERSION 3.14)

project(EmbeddedIntentRecognizer)

# C++17 so can work with C++20
set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(src)
