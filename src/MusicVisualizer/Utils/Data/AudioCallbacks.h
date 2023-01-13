//
// Created by yukari on 1/12/23.
//

#ifndef MUSICVISUALIZER_AUDIOCALLBACKS_H
#define MUSICVISUALIZER_AUDIOCALLBACKS_H

#include <deque>
#include "AudioHandling/IAudioCallback.h"

namespace mvlizer::data {

        class AudioCallbacks : public IAudioCallback {
        public:
            /**
             * @inherit
             */
            PaStreamCallbackResult OnCall(
                    const float* inputBuffer,
                    const float* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags flags
            ) override;

            /**
             * @inherit
             */
            void OnFinish() override;

            std::deque<float> audio_data;

        };

    } // data

#endif //MUSICVISUALIZER_AUDIOCALLBACKS_H
