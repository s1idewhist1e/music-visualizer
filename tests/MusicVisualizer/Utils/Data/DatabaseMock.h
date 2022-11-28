#pragma once
#ifndef DATABASE_MOCK_H
#define DATABASE_MOCK_H
#include <gmock/gmock.h>
#include "../../../src/MusicVisualizer/Utils/Data/Database.h"

namespace mvlizer {
	namespace tests {
		class MockDatabase : public mvlizer::Database {
		public:
	/*		MOCK_METHOD(void, setUpdateTime, (double time), (override));
			MOCK_METHOD(double, getUpdateTime, (), (override));
			MOCK_METHOD(void, setRenderTime, (double time), (override));
			MOCK_METHOD(double, getRenderTime, (), (override));*/
		};
	}
}

#endif