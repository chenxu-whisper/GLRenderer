# 收集wrapper目录下的所有.cpp文件
file(GLOB_RECURSE WRAPPER_SOURCES Wrapper/*.cpp)
file(GLOB_RECURSE APPLICATION_SOURCES Application/*.cpp)
# 添加Framework目录的源文件收集
file(GLOB_RECURSE FRAMEWORK_SOURCES Framework/*.cpp)

# 创建wrapperLib静态库
add_library(WrapperLib STATIC ${WRAPPER_SOURCES})
# 创建applicationLib静态库
add_library(ApplicationLib STATIC ${APPLICATION_SOURCES} ${FRAMEWORK_SOURCES}
        ../Include/Core.h)

# 为wrapperLib库设置包含目录
target_include_directories(WrapperLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Wrapper)
target_include_directories(WrapperLib PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/Include)
# 为applicationLib库设置包含目录
target_include_directories(ApplicationLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Application
        ${CMAKE_CURRENT_SOURCE_DIR}/Framework
        ${CMAKE_SOURCE_DIR}/Include
        ${CMAKE_SOURCE_DIR}/Include/Application
        ${CMAKE_SOURCE_DIR}/Include/Framework)
target_include_directories(ApplicationLib PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/Include)

# 创建主可执行文件
file(GLOB_RECURSE MAIN_SOURCES *.cpp *c)
add_executable(GLRenderer ${MAIN_SOURCES} )

# 为主可执行文件设置包含目录
target_include_directories(GLRenderer PRIVATE
        ${CMAKE_SOURCE_DIR}/Include
        ${CMAKE_SOURCE_DIR}/Include/Framework
        ${CMAKE_SOURCE_DIR}/ThirdParty/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/Wrapper
        ${CMAKE_CURRENT_SOURCE_DIR}/Framework
)

# 链接库
target_link_libraries(GLRenderer PRIVATE
        WrapperLib
        ApplicationLib
        ${CMAKE_SOURCE_DIR}/ThirdParty/Lib/libglfw3.a
)

# 在Windows平台上可能需要额外的系统库
if(WIN32)

endif()