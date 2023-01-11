#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MusicVisualizer.h"
#include "../../LoggerMock.h"
#include "../Rendering/Objects/IRenderObjectMock.h"
#include <memory>
#include <thread>
#include <chrono>

namespace mvlizer::rendering { // NOLINT(modernize-concat-nested-namespaces)
	namespace tests {

		class DatabaseTests : public ::testing::Test {
		protected:
			mvlizer::data::Database database;
			std::shared_ptr<::testing::NiceMock<mvlizer::tests::MockLogger>> logger;

			void SetUp() override {
				logger = std::make_shared<::testing::NiceMock<mvlizer::tests::MockLogger>>();
                std::shared_ptr<spikeylog::ILogger> logger_tmp = logger;
				this->database.Init(logger_tmp);
				this->database.renderObjects = { new MockIRenderObject(), new MockIRenderObject(), new MockIRenderObject() };
				EXPECT_CALL(*logger, err)
					.Times(0);
			}
		};

        TEST_F(DatabaseTests, asdf) {
            ASSERT_TRUE(true);
        }

		class DatabaseTests_Update : public DatabaseTests { };

		TEST_F(DatabaseTests_Update, calls_update_on_render_objects) {
			static const int NUMS_TO_TRY = 5;

			for (auto obj : database.renderObjects) {
				EXPECT_CALL(*(MockIRenderObject*)obj, tick())
					.Times(NUMS_TO_TRY);
			}

			for (int i = 0; i < NUMS_TO_TRY; i++) {
				database.update();
			}
		}

		class DatabaseTests_ThreadSafety : public DatabaseTests { };

		TEST_F(DatabaseTests_ThreadSafety, gets) {
			database.setUpdateTime(0);

			std::mutex mtx;
			mtx.lock();
			double updatetime_1, updatetime_2;
			std::thread a([this, &updatetime_1, &mtx]() {
				//std::cout << "a" << std::endl;
				mtx.unlock();
				updatetime_1 = database.getUpdateTime();
				});

            mtx.lock();
            mtx.unlock();
			for (int i = 0; i < 5; i++);
			database.setUpdateTime(1);


			std::thread b([this,&updatetime_2]() {
				updatetime_2 = database.getUpdateTime();
				//std::cout << "b" << std::endl;
				});

			a.join();
			b.join();

//			EXPECT_EQ(updatetime_1, 0.0);
//			EXPECT_EQ(updatetime_2, 1.0);

			database.setRenderTime(0);

			double rendertime_1, rendertime_2;
			mtx.lock();
			std::thread c([this, &rendertime_1, &mtx]() {
				//std::cout << "a" << std::endl;
				mtx.unlock();
				rendertime_1 = database.getRenderTime();
				});

			mtx.lock();
			mtx.unlock();
			database.setRenderTime(1);


			std::thread d([this, &rendertime_2]() {
				rendertime_2 = database.getRenderTime();
				//std::cout << "b" << std::endl;
				});

			c.join();
			d.join();

//			EXPECT_EQ(rendertime_1, 0.0);
//			EXPECT_EQ(rendertime_2, 1.0);
		}

		TEST_F(DatabaseTests_ThreadSafety, sets) {
			std::mutex mtx;

			database.setUpdateTime(0);
			double updatetime_1 = database.getUpdateTime();
			mtx.lock();
			std::thread a([this, &mtx]() {
				mtx.unlock();
				database.setUpdateTime(1);
				});
			mtx.lock();
			mtx.unlock();
			double updatetime_2 = database.getUpdateTime();

			a.join();

			EXPECT_NE(updatetime_1, updatetime_2);
			EXPECT_EQ(updatetime_1, 0);
			EXPECT_EQ(updatetime_2, 1);



			database.setRenderTime(0);
			double rendertime_1 = database.getRenderTime();
			mtx.lock();
			std::thread b([this, &mtx]() {
				mtx.unlock();
				database.setRenderTime(1);
				});
			mtx.lock();
			mtx.unlock();
			double rendertime_2 = database.getRenderTime();

			b.join();

			EXPECT_NE(rendertime_1, rendertime_2);
			EXPECT_EQ(rendertime_1, 0);
			EXPECT_EQ(rendertime_2, 1);
		}
	}
}