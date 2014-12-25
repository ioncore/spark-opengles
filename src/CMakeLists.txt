cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0020 OLD)

project(SPARK_LIB)
set(SPARK_LIB_NAME ${PROJECT_NAME})

find_package(OpenGLES REQUIRED)
#find_package(FreeType REQUIRED)

message("message OpenGL include dir: ${OpenGL_INCLUDE_DIR}")
message("message FREETYPE_INCLUDE_DIR: ${FREETYPE_INCLUDE_DIR}")
message("message gl libs: ${OPENGL_gl_LIBRARY}")

include_directories(
    ../include
    ${OpenGL_INCLUDE_DIR}
    #/usr/local/include/
    ${FREETYPE_INCLUDE_DIR}
    OpenGLES/
#    /Users/dovgalkostiantyn/Downloads/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.1.sdk/System/Library/Frameworks/OpenGLES.framework/Headers/
#    /Users/dovgalkostiantyn/Downloads/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator7.1.sdk/System/Library/Frameworks/OpenGLES.framework/Headers/
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

target_link_libraries(
    ${SPARK_LIB_NAME}
    #${OpenGL_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
)

