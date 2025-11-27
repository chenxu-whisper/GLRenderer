# 收集wrapper目录下的所有.cpp文件
file(GLOB_RECURSE WRAPPER_SOURCES wrapper/*.cpp)

# 创建wrapperLib静态库
add_library(wrapperLib STATIC ${WRAPPER_SOURCES})

# 为wrapperLib库设置包含目录
target_include_directories(wrapperLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/wrapper)
target_include_directories(wrapperLib PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/include)

# 创建主可执行文件
file(GLOB_RECURSE MAIN_SOURCES *.cpp *c)
add_executable(GLRenderer ${MAIN_SOURCES} )

# 为主可执行文件设置包含目录
target_include_directories(GLRenderer PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/thirdParty/include
        ${CMAKE_CURRENT_SOURCE_DIR}/wrapper
)

# 链接库
target_link_libraries(GLRenderer PRIVATE
        wrapperLib
        ${CMAKE_SOURCE_DIR}/thirdParty/lib/libglfw3.a
)

# 在Windows平台上可能需要额外的系统库
if(WIN32)
    target_link_libraries(GLRenderer PRIVATE opengl32 gdi32)
endif()