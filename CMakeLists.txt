# 最小cmake版本
cmake_minimum_required(VERSION 3.10)
# 项目名称
project(GLRenderer)
# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

# 定义着色器文件路径
set(SHADER_FILES
        "Asset/Shader/Vertex.vert"
        "Asset/Shader/Fragment.frag"
)

# 为每个着色器文件创建复制命令
foreach(SHADER ${SHADER_FILES})
    # 获取目标路径
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(DEST_PATH "${CMAKE_BINARY_DIR}/${SHADER}")

    # 创建自定义命令，当天源文件改变时执行复制
    add_custom_command(
            OUTPUT ${DEST_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/${SHADER} ${DEST_PATH}
            DEPENDS ${CMAKE_SOURCE_DIR}/${SHADER}
            COMMENT "Copying ${SHADER} to build directory"
    )

    # 将目标添加到列表中
    list(APPEND SHADER_TARGETS ${DEST_PATH})
endforeach()

# 创建自定义目标，依赖于所有着色器文件的复制
add_custom_target(CopyShaders ALL DEPENDS ${SHADER_TARGETS})

# 全局预编译宏
add_definitions(-DDEBUG)
# 添加src子目录
add_subdirectory(Src)

# 确保主可执行文件依赖于着色器复制目标
add_dependencies(GLRenderer CopyShaders)
