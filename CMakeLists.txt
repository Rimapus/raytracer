cmake_minimum_required(VERSION 3.16)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(src/Parser)
add_subdirectory(src/Core)

file(GLOB_RECURSE RAYTRACER_SRC CONFIGURE_DEPENDS src/*.cpp)

add_executable(raytracer
    ${RAYTRACER_SRC}
)

target_compile_options(raytracer PRIVATE
    -Wall
    -Wextra
)

target_include_directories(raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(raytracer PRIVATE
    parser
    core
)
