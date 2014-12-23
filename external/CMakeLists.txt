cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0020 OLD)

project(THIRD_PARTIES)

find_package(PkgConfig)

#add_subdirectory(SDL2)
add_subdirectory(freetype)

