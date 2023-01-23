//
// Created by yukari on 1/12/23.
//

#include <mutex>
#include <iostream>
#include "AudioCallbacks.h"

namespace mvlizer::data {
    std::pair<std::deque<float>, std::deque<float>> AudioCallbacks::GetAudioData() {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return std::make_pair(audio_data_r, audio_data_l);
    }

    PaStreamCallbackResult
    AudioCallbacks::OnCall(const int32_t* inputBuffer, const int32_t* outputBuffer, unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags flags) {
        {
            std::unique_lock<std::shared_mutex> lk(mtx);
            for (unsigned long i = 0; i < framesPerBuffer; i+=2) {
//                if (std::abs(inputBuffer[i]) > 1)
//                    std::cout << inputBuffer[i] << std::endl;
                audio_data_r.push_front(inputBuffer[i] / (double) INT32_MAX);
                audio_data_r.pop_back();

                audio_data_l.push_front(inputBuffer[i + 1] / (double) INT32_MAX);
                audio_data_l.pop_back();
            }
        }
        return paContinue;
    }

    void AudioCallbacks::OnFinish() {

    }

    AudioCallbacks::AudioCallbacks(unsigned long total_num_frames, unsigned long frames_per_buffer)
            : data_size{total_num_frames},
              buffer_size{frames_per_buffer},
              audio_data_l(total_num_frames, 0.0f),
              audio_data_r(total_num_frames, 0.0f) {

    }
} // data