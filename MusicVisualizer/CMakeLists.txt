# CMakeList.txt : CMake project for MusicVisualizer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



# Add source to this project's executable.

find_package(OpenGL REQUIRED)
add_subdirectory("vendor/glew")
add_subdirectory("vendor/glfw3")
add_subdirectory("vendor/spikeylog")
add_subdirectory("vendor/portaudio")

# message(${OPENGL_LIBRARIES} "\n")
message("${OPENGL_INCLUDE_DIRS}")

include_directories ("src" ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

file (GLOB_RECURSE MV_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable (MusicVisualizer ${MV_SOURCES} "src/Utils/Rendering/Objects/Vertex.h" "src/Utils/Rendering/Objects/TestRenderObject.cpp" "src/Utils/Rendering/Objects/TestRenderObject.h" "src/Utils/Rendering/Objects/VisualizerObject.cpp")
target_link_libraries (MusicVisualizer glfw glew spikeylog PortAudio ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
# target_link_libraries (MusicVisualizer glfw)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicVisualizer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
