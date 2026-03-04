cmake_minimum_required(VERSION 3.10)
project(GLRenderer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## 全局预编译宏
add_definitions(-DDEBUG)

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# 添加头文件目录 - 确保所有头文件都能被正确找到
include_directories(
        ${CMAKE_SOURCE_DIR}/Include
        ${CMAKE_SOURCE_DIR}/Include/Wrapper
        ${CMAKE_SOURCE_DIR}/Include/Application
        ${CMAKE_SOURCE_DIR}/Include/Framework
        ${CMAKE_SOURCE_DIR}/ThirdParty/Include
        ${CMAKE_SOURCE_DIR}/ThirdParty/Include/GLFW
        ${CMAKE_SOURCE_DIR}/ThirdParty/Include/glad
        ${CMAKE_SOURCE_DIR}/ThirdParty/Include/glm
)

# 收集所有源文件
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/Src/*.cpp
        ${CMAKE_SOURCE_DIR}/Src/*.c
)

# 查看收集到的源文件 - 用于调试
message("收集到的源文件:")
foreach(source ${SOURCES})
    message("  ${source}")
endforeach()

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES}
        Src/Application/Camera/Camera.cpp
        Include/Application/Camera/Camera.h
        Src/Application/Camera/OrthographicCamera.cpp
        Include/Application/Camera/OrthographicCamera.h
        Src/Application/Camera/PerspectiveCamera.cpp
        Include/Application/Camera/PerspectiveCamera.h
        Src/Application/Camera/CameraControl.cpp
        Include/Application/Camera/CameraControl.h
        Src/Application/Camera/TrackBallCameraControl.cpp
        Include/Application/Camera/TrackBallCameraControl.h
        Src/Application/Camera/GameCameraControl.cpp
        Include/Application/Camera/GameCameraControl.h
)

# 链接库
target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/ThirdParty/Lib/libglfw3.a
)

# 如果是Windows系统，添加额外的库
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()

# 添加资源目录编译定义，支持运行时直接从源目录加载资源
# 这样程序可以直接访问源目录中的资源文件，修改后无需重新构建
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/Asset/")

# 简化资源复制，只在构建时复制一次，开发时使用源目录资源
add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Asset
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Asset
        COMMENT "Copying assets to output directory..."
)