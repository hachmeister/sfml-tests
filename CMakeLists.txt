cmake_minimum_required(VERSION 2.6)

# Project name.
project(SFML_TESTS)

# Set version number
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

# Set default install prefix.
if(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build: Debug Release." FORCE)
endif()

# Set flags.
set(CMAKE_CXX_FLAGS         "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -Wall -g -DDEBUG")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(
)

add_executable(texture
  texture.cc
)

target_link_libraries(texture
  sfml-graphics
  sfml-window
  sfml-system
#  dl
#  GL
)
