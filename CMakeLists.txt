cmake_minimum_required(VERSION 3.8)

project(lib3d_rotation)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_TARGET_LIB_NAME "3d_rotation")

add_subdirectory(src)

include(3d_rotation_build_options)
