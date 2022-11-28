#include <gtest/gtest.h>
#include "MusicVisualizer/MusicVisualizer.h"

TEST(name1, name2) {
	mvlizer::Database data;
	data.should_close = false;
	ASSERT_FALSE(data.should_close);
}