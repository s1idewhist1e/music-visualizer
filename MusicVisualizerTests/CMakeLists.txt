include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file (GLOB_RECURSE MV_TESTS CONFIGURE_DEPENDS "src/**.cpp")

enable_testing()

add_executable(MusicVisualizerTests ${MV_TESTS})

target_link_libraries(MusicVisualizerTests
	MusicVisualizerlib
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MusicVisualizerTests)
