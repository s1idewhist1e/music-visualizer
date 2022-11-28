#include <gtest/gtest.h>
#include "MusicVisualizer/MusicVisualizer.h"
#include "Utils/Data/DatabaseMock.h"
#include "Utils/Rendering/Objects/IRenderObjectMock.h"
#include "LoggerMock.h"

#include <iostream>

namespace mvlizer {
	namespace tests {
		class MusicVisualizerTests : public ::testing::Test {
		protected:
			MockDatabase data;
			std::shared_ptr<spikeylog::ILogger> logger;
			void SetUp() override {
				logger = std::unique_ptr<spikeylog::ILogger>(new MockLogger());
			}
		};


	}
}