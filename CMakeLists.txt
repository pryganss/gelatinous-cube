cmake_minimum_required(VERSION 3.10)

# Project initialisation
project(gelatinous-cube VERSION 1.0)
set(gelatinous-cube_VERSION_YEAR 2022)
set(gelatinous-cube_OUTPUT_NAME gelatinous-cube)

# Build configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(gelatinous-cube_CODE_SOURCE_DIR ${gelatinous-cube_SOURCE_DIR}/src)

set(gelatinous-cube_SOURCES
    main.cc)

list(TRANSFORM gelatinous-cube_SOURCES
     PREPEND "${gelatinous-cube_CODE_SOURCE_DIR}/")

add_executable(${gelatinous-cube_OUTPUT_NAME} ${gelatinous-cube_SOURCES})

set(gelatinous-cube_CXX_LIBRARIES
    ${CURSES_LIBRARIES})

target_link_libraries(${gelatinous-cube_OUTPUT_NAME}
                      ${gelatinous-cube_CXX_LIBRARIES})
