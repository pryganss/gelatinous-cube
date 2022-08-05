cmake_minimum_required(VERSION 3.10)

# Project initialisation
project(gelcube VERSION 1.0)
set(gelcube_VERSION_YEAR 2022)

# Libraries
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

find_package(Boost
             1.79.0
             REQUIRED
             COMPONENTS program_options)

# Build configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(gelcube_CODE_SOURCE_DIR ${gelcube_SOURCE_DIR}/src)

set(gelcube_SOURCES
    main.cc
    options.cc
    tui.cc)

list(TRANSFORM gelcube_SOURCES
     PREPEND "${gelcube_CODE_SOURCE_DIR}/")

add_executable(${CMAKE_PROJECT_NAME} ${gelcube_SOURCES})

set(gelcube_CXX_LIBRARIES
    ${CURSES_LIBRARIES})

target_link_libraries(${CMAKE_PROJECT_NAME} ${gelcube_CXX_LIBRARIES})

# Internationalization
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/i18n.cmake)

# Install
install(TARGETS gelcube
    RUNTIME
    DESTINATION bin)

file(GLOB PO_LANGS LIST_DIRECTORIES true ${CMAKE_LOCALE_BINARY_DIR}/*)
foreach(PO_LANG IN ITEMS ${PO_LANGS})
    if(IS_DIRECTORY ${PO_LANG})
        message(STATUS ${PO_LANG})
        install(DIRECTORY ${PO_LANG}
                DESTINATION locale)
    endif()
endforeach()

# Uninstall
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND
            ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)
endif()
