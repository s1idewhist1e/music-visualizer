cmake_minimum_required (VERSION 3.1)

find_package(OpenGL REQUIRED)
add_subdirectory("vendor/glew")
add_subdirectory("vendor/glfw3")
add_subdirectory("vendor/spikeylog")
add_subdirectory("vendor/portaudio")

include_directories ("src" ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

file (GLOB_RECURSE MV_SOURCES CONFIGURE_DEPENDS "src/**.cpp")

add_executable (MusicVisualizer ${MV_SOURCES} "src/Utils/Math/PolygonMath.h" "src/Utils/Math/PolygonMath.cpp")
target_link_libraries (MusicVisualizer glfw glew spikeylog PortAudio ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicVisualizer PROPERTY CXX_STANDARD 20)
endif()