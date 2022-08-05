# Internationalization
find_package(Intl REQUIRED)
if(Intl_FOUND)
    message(STATUS "Internationalization found:")
    message(STATUS " INTL_INCLUDE_DIRS: ${Intl_INCLUDE_DIRS}")
    message(STATUS " INTL_LIBRARIES: ${Intl_LIBRARIES}")
    message(STATUS " Version: ${Intl_VERSION}")
    include_directories(${Intl_INCLUDE_DIRS})
    link_directories(${Intl_LIBRARY_DIRS})
else()
    message(STATUS "Internationalization not found!")
endif()

find_package(Gettext REQUIRED)
if(Gettext_FOUND)
    message(STATUS "gettext found:")
    message(STATUS " Version: ${GETTEXT_VERSION_STRING}")
else()
    message(STATUS "gettext not found!")
endif()

find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext)
find_program(GETTEXT_MSGMERGE_EXECUTABLE msgmerge)
find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

set(CMAKE_LOCALE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/locale)
set(CMAKE_LOCALE_BINARY_DIR ${CMAKE_BINARY_DIR}/locale)

if(GETTEXT_XGETTEXT_EXECUTABLE)
    message(DEBUG " xgettext: ${GETTEXT_XGETTEXT_EXECUTABLE}")

    add_custom_target(
        pot-update
        DEPENDS "${CMAKE_LOCALE_SOURCE_DIR}/${OUTPUT_NAME}.pot"
        COMMENT "pot-update: Done.")

    add_custom_command(
        OUTPUT "${CMAKE_LOCALE_SOURCE_DIR}/${OUTPUT_NAME}.pot"
        COMMAND
            ${CMAKE_COMMAND}
                -E make_directory "${CMAKE_LOCALE_SOURCE_DIR}"
        COMMAND
            ${GETTEXT_XGETTEXT_EXECUTABLE}
                --from-code=utf-8
                --force-po
                --output=${CMAKE_LOCALE_SOURCE_DIR}/${OUTPUT_NAME}.pot
                --keyword=_
                --width=80
                ${${CMAKE_PROJECT_NAME}_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "pot-update: pot file generated: \
                 ${CMAKE_LOCALE_SOURCE_DIR}/${OUTPUT_NAME}.pot")
endif(GETTEXT_XGETTEXT_EXECUTABLE)

if(GETTEXT_MSGMERGE_EXECUTABLE)
    message(DEBUG " msgmerge: ${GETTEXT_MSGMERGE_EXECUTABLE}")

    add_custom_target(
        pot-merge
        COMMENT "pot-merge: Done."
        DEPENDS ${CMAKE_LOCALE_SOURCE_DIR}/${OUTPUT_NAME}.pot)

    file(GLOB PO_FILES ${CMAKE_LOCALE_SOURCE_DIR}/*.po)
    message(TRACE " PO_FILES: ${PO_FILES}")

    foreach(PO_FILE IN ITEMS ${PO_FILES})
        message(STATUS " Adding msgmerge for: ${PO_FILE}")
        add_custom_command(
            TARGET pot-merge
            PRE_BUILD
            COMMAND
                ${GETTEXT_MSGMERGE_EXECUTABLE}
                    ${PO_FILE}
                    ${CMAKE_LOCALE_SOURCE_DIR}/${OUTPUT_NAME}.pot
            COMMENT "pot-merge: ${PO_FILE}")
    endforeach()
endif(GETTEXT_MSGMERGE_EXECUTABLE)

if(GETTEXT_MSGFMT_EXECUTABLE)
    message(DEBUG " msgmerge: ${GETTEXT_MSGFMT_EXECUTABLE}")
    message(TRACE " PO_LANGS: ${PO_LANGS}")

    add_custom_target(
        po-compile
        COMMENT "po-compile: Done.")

    file(GLOB PO_FILES ${CMAKE_LOCALE_SOURCE_DIR}/*.po)
    message(TRACE " PO_FILES: ${PO_FILES}")

    foreach(PO_FILE IN ITEMS ${PO_FILES})
        get_filename_component(PO_LANG
            ${PO_FILE}
            NAME_WE)

        message(STATUS " Adding msgfmt for: ${PO_LANG}")
        add_custom_command(
            TARGET po-compile
            PRE_BUILD
            COMMAND
                ${CMAKE_COMMAND} -E make_directory
                    ${CMAKE_LOCALE_BINARY_DIR}/${PO_LANG}/LC_MESSAGES
            COMMAND
                ${GETTEXT_MSGFMT_EXECUTABLE}
                    --output-file=${CMAKE_LOCALE_BINARY_DIR}/${PO_LANG}/LC_MESSAGES/${OUTPUT_NAME}.mo
                    ${PO_FILE}
            COMMENT "po-compile: ${PO_LANG}")
    endforeach()
endif(GETTEXT_MSGFMT_EXECUTABLE)
