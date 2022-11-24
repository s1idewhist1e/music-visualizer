find_package(OpenGL REQUIRED)

include_directories (${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

file (GLOB_RECURSE MV_SOURCES CONFIGURE_DEPENDS "**.cpp")

add_executable (MusicVisualizer ${MV_SOURCES})
target_link_libraries (MusicVisualizer glfw glew spikeylog PortAudio ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})