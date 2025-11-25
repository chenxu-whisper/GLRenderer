# 查找src下所有源文件
file(GLOB_RECURSE SRC_FILES "*.cpp")
# 将src_files作为lib库添加
add_library(src_libs ${SRC_FILES})

