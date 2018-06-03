cmake_minimum_required(VERSION 3.7.2)
project(boilerplate)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -g")

# Add SFML
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

set(HEADER_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB HEADER_FILES "include/*.h")
file(GLOB SOURCES "src/*.cpp")

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

# Tests executable
file(GLOB TESTS "test/*.cpp")
add_executable(tests ${TESTS} ${SOURCES} ${HEADER_FILES})
target_include_directories(tests PRIVATE ${HEADER_DIRECTORIES})
