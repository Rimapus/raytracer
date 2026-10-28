cmake_minimum_required(VERSION 3.16)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGXX REQUIRED IMPORTED_TARGET libconfig++)

add_library(parser
    Parser.cpp
)

target_compile_options(parser PRIVATE
    -Wall
    -Wextra
)

target_link_libraries(parser PRIVATE
    PkgConfig::LIBCONFIGXX
)

target_include_directories(parser PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
