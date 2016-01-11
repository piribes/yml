cmake_minimum_required(VERSION 3.4)

project(yml)
set(YML_VERSION_MAJOR 0)
set(YML_VERSION_MINOR 0)
set(YML_VERSION_PATCH 1)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
                      ${CMAKE_MODULE_PATH})
include_directories(src ${CMAKE_CURRENT_BINARY_DIR})

# yml
configure_file(config.h.in config.h)
set(YML_HEADERS)
set(YML_SOURCES src/main.cpp)
add_executable(yml ${YML_SOURCES} ${YML_HEADERS})
add_definitions(-std=c++14)

# yaml-cpp
find_package(YamlCpp)

if(YAMLCPP_FOUND)
    include_directories(${YAMLCPP_INCLUDE_DIR})
    target_link_libraries(yml ${YAMLCPP_LIBRARY})
endif()
