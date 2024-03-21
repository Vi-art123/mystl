cmake_minimum_required(VERSION 3.16)
project(mystl)

set(CMAKE_CXX_STANDARD 20)

# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/BinaryTree)
include_directories(${PROJECT_SOURCE_DIR}/List)
include_directories(${PROJECT_SOURCE_DIR}/ArrayList)
include_directories(${PROJECT_SOURCE_DIR}/LinkedList)
include_directories(${PROJECT_SOURCE_DIR}/Stack)
include_directories(${PROJECT_SOURCE_DIR}/Queue)

# 添加一个可执行文件
add_executable(mystl main.cpp)
