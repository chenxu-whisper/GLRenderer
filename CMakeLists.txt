# 最小cmake版本
cmake_minimum_required(VERSION 3.10)
# 项目名称
project(GLRenderer)
# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

# 包含第三方库头文件
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)

# 添加可执行文件
add_executable(GLRenderer src/main.cpp src/glad.c)

# 链接glfw3库
target_link_libraries(GLRenderer ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib/libglfw3.a)
