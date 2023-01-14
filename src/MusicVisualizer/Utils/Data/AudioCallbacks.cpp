//
// Created by yukari on 1/12/23.
//

#include <mutex>
#include "AudioCallbacks.h"

namespace mvlizer::data {
    std::deque<float> AudioCallbacks::GetAudioData() {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return audio_data;
    }

    PaStreamCallbackResult
    AudioCallbacks::OnCall(const float* inputBuffer, const float* outputBuffer, unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags flags) {
        {
            std::unique_lock<std::shared_mutex> lk(mtx);
            for (unsigned long i = 0; i < framesPerBuffer; i++) {
                audio_data.push_front(inputBuffer[i]);
                audio_data.pop_back();
            }
        }
        return paContinue;
    }

    void AudioCallbacks::OnFinish() {

    }

    AudioCallbacks::AudioCallbacks(unsigned long total_num_frames, unsigned long frames_per_buffer)
    : data_size{total_num_frames},
    buffer_size{frames_per_buffer},
    audio_data(total_num_frames, 0.0f){

    }
} // data