cmake_minimum_required(VERSION 3.16)
project(tris-stalker VERSION 1.0 LANGUAGES CXX)

set(VERSION "1.0")
configure_file (config.h.in config.h)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Look for neccesary packages of Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Directories for source files
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add the executable files
add_executable(tris-stalker
	${SOURCE_DIR}/app/main.cpp
)

# Directory for the target add_executable)
set_target_properties(tris-stalker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

target_include_directories(tris-stalker PRIVATE
	${SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR} # For config.h
)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
