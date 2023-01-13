//
// Created by sekibanki on 1/10/23.
//

#ifndef MUSICVISUALIZER_CALLBACKSMOCK_H
#define MUSICVISUALIZER_CALLBACKSMOCK_H

#include <gmock/gmock.h>
#include "MusicVisualizer/Utils/Data/PortAudioStream.h"

namespace mvlizer::data {
    namespace tests {
        class MockPortAudioCallbacks : public IAudioCallback {
        public:

            std::mutex mtx;
            std::condition_variable cv;

            MockPortAudioCallbacks() {

            }

            int on_call_count = 0;
            int on_finish_count = 0;

            PaStreamCallbackResult OnCall(
                    const float* inputBuffer,
                    const float* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags flags
                    ) override {
                on_call_count++;
                return paComplete;
            }

            void OnFinish() override {
                   on_finish_count++;
                   std::cout << "Finish Callback Called" << std::endl;
                   cv.notify_all();
            }

        };
    }

}

#endif //MUSICVISUALIZER_CALLBACKSMOCK_H
