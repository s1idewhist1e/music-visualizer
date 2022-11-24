add_subdirectory("glew")
add_subdirectory("glfw3")
add_subdirectory("portaudio")
add_subdirectory("spikeylog")
add_subdirectory("googletest")

# to suppress glew warnings
set_target_properties(glew PROPERTIES COMPILE_FLAGS "-w")
