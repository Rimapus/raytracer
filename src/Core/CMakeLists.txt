file(GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS *.cpp)

add_library(core STATIC
    ${CORE_SRC}
)

target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(core PUBLIC
    parser
    SFML::Graphics
    SFML::Window
    SFML::System
)
