cmake_minimum_required(VERSION 3.10)
project(life VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

include_directories(include)
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
if (SFML_FOUND)
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
else()
    message(FATAL_ERROR "SFML not found")
endif()
