cmake_minimum_required(VERSION 3.16)
project(mystl)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/test)
include_directories(${PROJECT_SOURCE_DIR}/Time)
include_directories(${PROJECT_SOURCE_DIR}/BinaryTree)
include_directories(${PROJECT_SOURCE_DIR}/List)
include_directories(${PROJECT_SOURCE_DIR}/ArrayList)
include_directories(${PROJECT_SOURCE_DIR}/LinkedList)
include_directories(${PROJECT_SOURCE_DIR}/Stack)
include_directories(${PROJECT_SOURCE_DIR}/Heap)
include_directories(${PROJECT_SOURCE_DIR}/Queue)
include_directories(${PROJECT_SOURCE_DIR}/Set)
include_directories(${PROJECT_SOURCE_DIR}/Map)

include_directories(${PROJECT_SOURCE_DIR}/Sort/include)

aux_source_directory(./     SRC_FILES)
aux_source_directory(./test SRC_FILES)
aux_source_directory(./Time SRC_FILES)
aux_source_directory(./Sort SRC_FILES)

# 添加一个可执行文件
add_executable(mystl ${SRC_FILES})
