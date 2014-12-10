cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0020 OLD)

project(SPARK_DEMOS)

if(CMAKE_TOOLCHAIN_FILE)
    message("Toolchain set: ${CMAKE_TOOLCHAIN_FILE}")
    find_package(OpenGLES REQUIRED)
elseif()
    find_package(OpenGL REQUIRED)
endif()

#find_package(FreeType REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(SDL2 REQUIRED)

message("OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
message("OPENGLES_INCLUDE_DIR: ${OPENGLES_INCLUDE_DIR}")
message("SDL2_LIBRARY: ${SDL2_LIBRARY}")
message("spark lib dir: ${SPARK_LIB_BINARY_DIR}")
message("spark lib: ${SPARK_LIB_NAME}")

include_directories(
    ../include
    ${OPENGL_INCLUDE_DIR}
    ${OPENGLES_INCLUDE_DIR}
    #${SDL2_INCLUDE_DIR}
    /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/OpenGLES.framework/Headers
    /Users/dovgalkostiantyn/Downloads/SDL2-2.0.3/include
    #${SDL2_INCLUDE_DIR}
    #${FTGL_INCLUDE_DIR}
    #${FREETYPE_INCLUDE_DIR}
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
    #${SDL2_LIBRARY}
    ${SPARK_LIB_BINARY_DIR}
    /Users/dovgalkostiantyn/Library/Developer/Xcode/DerivedData/SDL-ajmbgrgmskuulcbzdmwlbwqzrnrs/Build/Products/Release-iphonesimulator
    /Library/Frameworks/SDL2.framework/Versions/Current
)

target_link_libraries(
    BasicDemo
    ${OpenGL_LIBRARY}
    ${OpenGLES_LIBRARY}
    #${SDL2_LIBRARY
    SPARK_LIB
    #/Users/dovgalkostiantyn/Library/Developer/Xcode/DerivedData/Demos-aysbywjmxxebbagzadwacbgaaujt/Build/Products/Debug-iphonesimulator/libSDL2.a
    /Users/dovgalkostiantyn/Library/Developer/Xcode/DerivedData/SDL-ajmbgrgmskuulcbzdmwlbwqzrnrs/Build/Products/Release-iphonesimulator/libSDL2.a
)

