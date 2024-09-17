cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(NewFile VERSION 1.0.0 LANGUAGES C CXX)

# --- Includes
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(properties)

# --- Dependencies
# add_subdirectory(dependencies)

# --- Project's sources
add_subdirectory(project)
