# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(convert CXX)

# 添加源文件
add_executable( convert 
                main.cpp 
                Parser.cpp
              )

# 指定包含目录，确保头文件可以被正确找到
target_include_directories(convert PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})