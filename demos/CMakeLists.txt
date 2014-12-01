cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0020 OLD)

project(SPARK_DEMOS)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)
#find_package(FTGL REQUIRED)
find_package(FreeType REQUIRED)

message("OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
message("SDL2_LIBRARY: ${SDL2_LIBRARY}")
message("spark lib dir: ${SPARK_LIB_BINARY_DIR}")
message("spark lib: ${SPARK_LIB_NAME}")

include_directories(
    ../include
    ${OPENGL_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
    #${FTGL_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIR}
    /usr/local/include/
    /usr/local/include/freetype2
)

add_executable(
    BasicDemo
    src/BasicDemo.cpp
)

add_dependencies(
    BasicDemo
    SPARK_LIB
)

link_directories(
    ${SDL2_LIBRARY}
    ${SPARK_LIB_BINARY_DIR}
)

target_link_libraries(
    BasicDemo
    #/Users/dovgalkostiantyn/projects/spark-opengles/bin/src/libSPARK_LIB.a
    ${OpenGL_LIBRARY}
    ${SDL2_LIBRARY}
    SPARK_LIB
)

