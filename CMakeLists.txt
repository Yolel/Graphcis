cmake_minimum_required(VERSION 3.21)
project(GraphcisTest4 C)

# 添加头文件
set(GLEW_H /opt/homebrew/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /opt/homebrew/Cellar/glfw/3.3.5/include/GLFW)

include_directories(${GLEW_H} ${GLFW_H} )

# 添加目标链接
set(GLEW_LINK /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.5/lib/libglfw.3.dylib)

link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} )

set(CMAKE_C_STANDARD 99)

add_executable(GraphcisTest4 main.c )

if (APPLE)
    target_link_libraries(GraphcisTest4 "-framework OpenGL")
    target_link_libraries(GraphcisTest4 "-framework glut")
endif()


