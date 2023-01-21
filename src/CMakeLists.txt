set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories (${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} "MusicVisualizer")

file (GLOB_RECURSE MV_LIB_SOURCES CONFIGURE_DEPENDS "MusicVisualizer/**.cpp")


add_library(MusicVisualizer_lib ${MV_LIB_SOURCES})
target_link_libraries (MusicVisualizer_lib
	glfw
	spikeylog 
	PortAudio
	OpenGL::GL
	GLEW::GLEW
)

target_include_directories (MusicVisualizer_lib PUBLIC "./MusicVisualizer")

add_executable (MusicVisualizer "Application.cpp")

target_link_libraries (MusicVisualizer MusicVisualizer_lib)