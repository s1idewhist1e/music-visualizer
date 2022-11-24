cmake_minimum_required (VERSION 3.18)



find_package(OpenGL REQUIRED)
add_subdirectory("vendor/glew")
add_subdirectory("vendor/glfw3")
add_subdirectory("vendor/spikeylog")
add_subdirectory("vendor/portaudio")

include_directories ("src" ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

file (GLOB_RECURSE MV_SOURCES CONFIGURE_DEPENDS "src/**.cpp")
file (GLOB_RECURSE MV_INCLUDE CONFIGURE_DEPENDS "src/**.h")

list (REMOVE_ITEM MV_SOURCES "src/MusicVisualizer.h")



add_library (MusicVisualizerlib ${MV_SOURCES})
target_include_directories (MusicVisualizerlib PUBLIC "src")

target_link_libraries (
	MusicVisualizerlib
	GTest::gtest_main
	glfw glew spikeylog 
	PortAudio 
	${OPENGL_LIBRARIES} 
	${GLEW_LIBRARIES}
)

add_executable (MusicVisualizer "src/MusicVisualizer.cpp")
target_link_libraries (MusicVisualizer MusicVisualizerlib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicVisualizer PROPERTY CXX_STANDARD 20)
endif()