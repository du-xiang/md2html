set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_minimum_required(VERSION 3.10)
project(convert CXX)

add_executable( convert 
                main.cpp 
                Parser.cpp
              )

target_include_directories(convert PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})