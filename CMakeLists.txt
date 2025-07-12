cmake_minimum_required(VERSION 3.16)
project(tris VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Look for neccesary packages of Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Directories for source files
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add the executable files
add_executable(tris
	${SOURCE_DIR}/app/main.cpp
)

# Directory for the target add_executable)
set_target_properties(tris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
