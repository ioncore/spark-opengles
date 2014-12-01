cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0020 OLD)

project(SPARK)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SPARK_SOURCE_DIR}/cmake" "${SPARK_SOURCE_DIR}/cmake/Utils")

add_subdirectory(cmake)
add_subdirectory(src)
add_subdirectory(demos)

