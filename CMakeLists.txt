# 最小cmake版本
cmake_minimum_required(VERSION 3.31)

# 项目名称
project(GLRenderer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

## 查找src下所有源文件
#aux_source_directory(./src SRC_FILES)

# 将asset文件夹中所有文件纳入到编译系统中
file(GLOB asset_libs "./asset")
# 复制asset文件夹中的所有文件到二进制目录
file(COPY ${asset_libs} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 将thirdParty文件夹中所有文件纳入到编译系统中
file(GLOB thirdParty_libs "./thirdParty")
# 复制thirdParty文件夹中的所有文件到二进制目录
file(COPY ${thirdParty_libs} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 将src文件夹中所有文件纳入到编译系统中
add_subdirectory(./src src_libs)

# 添加可执行文件
add_executable(GLRenderer src_libs)

# 链接src_libs库
target_link_libraries(GLRenderer src_libs)
