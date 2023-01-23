# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (MusicVisualizer VERSION 0.1)

option(GENERATE_DOCS "Generate documentation using doxygen \n\t (OFF | HTML | PDF | ALL)" OFF)


if (NOT (GENERATE_DOCS MATCHES OFF))
    find_package(Doxygen)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Creating Doxygen documentation"
            VERBATIM)
endif()

set(DOXYGEN_IN)

set (CMAKE_CXX_STANDARD 17)

include_directories("src")

add_subdirectory("lib" EXCLUDE_FROM_ALL)
add_subdirectory("src")
add_subdirectory("tests")
