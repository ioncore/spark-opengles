cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0020 OLD)

project(SPARK_LIB)
set(SPARK_LIB_NAME ${PROJECT_NAME})


FIND_LIBRARY(OpenGL_LIBRARY OpenGL)

message("message: ${OpenGL_LIBRARY}")

include_directories(
    ../include
    ${OpenGL_LIBRARY}
    /usr/local/include/
    /usr/local/include/freetype2
)

file(
	GLOB 
	SPARK_LIB_sources
    SPK_All.cpp    
    SPK_GL_All.cpp
)

file(
	GLOB 
	SPARK_LIB_headers
    ../include/SPK.h
    ../include/SPK_GL.h
)

add_library(
    ${SPARK_LIB_NAME}
	STATIC
    ${SPARK_LIB_sources}
	${SPARK_LIB_headers}
)

#add_executable(
#    demo
#    demos/src/BasicDemo.cpp
#    ${SPARK_LIB_headers}
#)

#add_dependencies(
#    demo
#    ${SPARK_LIB_NAME}
#    /Users/dovgalkostiantyn/Desktop/libSDL2Sim.a
#)

#target_link_libraries(
#    demo
#    ${OpenGL_LIBRARY}
#    ${SDL_LIBRARY}
#)
