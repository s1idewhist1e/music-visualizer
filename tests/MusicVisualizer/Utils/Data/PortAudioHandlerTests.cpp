//
// Created by sekibanki on 1/10/23.
//

#include <memory>
#include <chrono>

#include "CallbacksMock.h"
#include "../../LoggerMock.h"
#include "MusicVisualizer/Utils/Data/AudioHandling/PortAudioHandler.h"

namespace mvlizer::data {
    namespace tests {
        class PortAudioHandlerTest : public ::testing::Test {
        protected:
            std::shared_ptr<::testing::NiceMock<mvlizer::tests::MockLogger>> logger =
                    std::make_shared<::testing::NiceMock<mvlizer::tests::MockLogger>>();
            void SetUp() override {
                EXPECT_CALL(*logger, err)
                    .Times(0);
            }

        };

        using ::testing::_;
        TEST_F(PortAudioHandlerTest, callsStreamCallbacks) {

            PortAudioHandler handler(logger);

//            std::cout << "Output Device: " << Pa_GetDefaultInputDevice() << std::endl;

            auto callbacks = std::make_shared<MockPortAudioCallbacks>();

            auto audioStream = std::make_shared<PortAudioStream>(22'050,
                                                                 256,
                                                                 Pa_GetDefaultInputDevice(),
                                                                 1,
                                                                 Pa_GetDefaultInputDevice(),
                                                                 1,
                                                                 callbacks
            );

            handler.AddAudioStream(audioStream);

            std::unique_lock<std::mutex> lk(callbacks->mtx);

            using std::chrono_literals::operator ""s;
            callbacks->cv.wait_for(lk, 30s);

            EXPECT_GE(callbacks->on_finish_count, 1);
            EXPECT_EQ(callbacks->on_call_count, 1);
        }

        TEST_F(PortAudioHandlerTest, initializesAndTerminates) {
            PaError err = Pa_Terminate();

            EXPECT_NE(err, paNoError); // make sure not initialized

            {
                ASSERT_NO_THROW({
                                    PortAudioHandler handler(logger); // check to see if it initializes
                                });
            }

            err = Pa_Terminate();
            EXPECT_NE(err, paNoError); // make sure it is terminated
        }

        TEST_F(PortAudioHandlerTest, canGetDevices) {
            PortAudioHandler handler(logger);
            auto devices = handler.GetAudioDevices();
            EXPECT_GT(devices.size(), 0);
            for (auto& device : devices) {
                ASSERT_TRUE(device.name);
            }
        }
    }
}