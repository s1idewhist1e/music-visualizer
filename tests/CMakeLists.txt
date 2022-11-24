set (CMAKE_CXX_STANDARD 14)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

file (GLOB_RECURSE MV_TESTS "**.cpp")

add_executable(
	MusicVisualizerTests
	${MV_TESTS}
)

target_link_libraries(
	MusicVisualizerTests
	MusicVisualizer_lib
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MusicVisualizerTests)