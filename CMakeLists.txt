# 最小cmake版本
cmake_minimum_required(VERSION 3.10)
# 项目名称
project(GLRenderer)
# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
# 全局预编译宏
add_definitions(-DDEBUG)
# 添加src子目录
add_subdirectory(src)