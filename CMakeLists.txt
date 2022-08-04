cmake_minimum_required(VERSION 3.10)

# Project initialisation
project(gelcube VERSION 1.0)
set(gelcube_VERSION_YEAR 2022)
set(gelcube_OUTPUT_NAME gelcube)

# Build configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

find_package(Boost
             1.79.0
             REQUIRED
             COMPONENTS program_options)

set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(gelcube_CODE_SOURCE_DIR ${gelcube_SOURCE_DIR}/src)

set(gelcube_SOURCES
    main.cc
    options.cc
    tui.cc)

list(TRANSFORM gelcube_SOURCES
     PREPEND "${gelcube_CODE_SOURCE_DIR}/")

add_executable(${gelcube_OUTPUT_NAME} ${gelcube_SOURCES})

set(gelcube_CXX_LIBRARIES
    ${CURSES_LIBRARIES})

target_link_libraries(${gelcube_OUTPUT_NAME} ${gelcube_CXX_LIBRARIES})
