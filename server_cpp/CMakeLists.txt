cmake_minimum_required(VERSION 3.10)
SET(SOLUTION_NAME "server_cpp")
SET(MODULE_NAME "server_cpp")
SET(MODULE_NAME_CONFIG "server_cpp-config")
message(STATUS "Project: " ${MODULE_NAME})

project(${MODULE_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    # Set up wrapper scripts
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    message("Using ccache")
else()
    message("Cannot find ccache")
endif()

add_subdirectory(third_party/seasocks)
set(RAPIDJSON_INCLUDE ${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)
message( "-- RAPIDJSON_INCLUDE ${RAPIDJSON_INCLUDE}")

# Project setup:

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(${MODULE_NAME} ${SOURCES})

target_link_libraries (${MODULE_NAME} 
    PRIVATE 
    seasocks)

target_compile_features(${MODULE_NAME} 
    PUBLIC cxx_std_17)

target_include_directories(${MODULE_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
    ${RAPIDJSON_INCLUDE})

target_compile_definitions(${MODULE_NAME} 
    PRIVATE -D_EXPORT)
    