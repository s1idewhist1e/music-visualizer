# CMakeList.txt : CMake project for MusicVisualizer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



# Add source to this project's executable.

find_package(OpenGL REQUIRED)
add_subdirectory("vendor/glfw3")

include_directories ("src" ${OPENGL_INCLUDE_DIRS})

file (GLOB_RECURSE MV_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable (MusicVisualizer ${MV_SOURCES})
target_link_libraries (MusicVisualizer glfw  ${OPENGL_LIBRARIES})
# target_link_libraries (MusicVisualizer glfw)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicVisualizer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
