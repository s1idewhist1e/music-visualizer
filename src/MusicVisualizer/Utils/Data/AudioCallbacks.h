//
// Created by yukari on 1/12/23.
//

#ifndef MUSICVISUALIZER_AUDIOCALLBACKS_H
#define MUSICVISUALIZER_AUDIOCALLBACKS_H

#include <deque>
#include <shared_mutex>
#include "AudioHandling/IAudioCallback.h"

namespace mvlizer::data {

        class AudioCallbacks : public IAudioCallback {
        public:

            AudioCallbacks(unsigned long total_num_frames, unsigned long frames_per_buffer);

            /**
             * @inherit
             */
            PaStreamCallbackResult OnCall(
                    const int32_t* inputBuffer,
                    const int32_t* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags flags
            ) override;

            /**
             * @inherit
             */
            void OnFinish() override;

            std::deque<float> GetAudioData();

        private:
            std::deque<float> audio_data;
            std::shared_mutex mtx;

            unsigned long data_size;
            unsigned long buffer_size;

        };

    } // data

#endif //MUSICVISUALIZER_AUDIOCALLBACKS_H
