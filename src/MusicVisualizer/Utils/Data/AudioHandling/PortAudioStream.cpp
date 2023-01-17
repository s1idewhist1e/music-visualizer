//
// Created by sekibanki on 1/10/23.
//

#include <memory>
#include "PortAudioStream.h"

namespace mvlizer::data {
        PortAudioStream::operator PaStream*() {
            return inner_stream;
        }

        PortAudioStream::PortAudioStream(double sampleRate, unsigned long framesPerBuffer, PaDeviceIndex inDevice,
                                         int inChannelCount, PaDeviceIndex outDevice, int outChannelCount,
                                         std::shared_ptr<IAudioCallback> callbacks)
                : SampleRate{sampleRate},
                  FramesPerBuffer{framesPerBuffer},
                  inner_stream{nullptr},
                  callbacks{std::move(callbacks)},

                  inputParameters{getParams(inDevice, inChannelCount)},
                  outputParameters{getParams(outDevice, outChannelCount)
                  } {

        }

        PortAudioStreamOpenParameters PortAudioStream::GetOpenParams() {
            return {
                    .stream             = &inner_stream,
                    .inParams           = inputParameters.device ? &inputParameters : nullptr,
                    .outParams          = outputParameters.device ? &outputParameters : nullptr,
                    .sampleRate         = SampleRate,
                    .framesPerBuffer    = FramesPerBuffer,
                    .flags              = paClipOff,
                    .userData           = this
            };
        }

        PaStreamCallbackResult
        PortAudioStream::callback(const int32_t* inputBuffer, const int32_t* outputBuffer, unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags flags) {
            return callbacks->OnCall(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, flags);
        }

    void PortAudioStream::finished_callback() {
            callbacks->OnFinish();
    }

    PaStreamParameters PortAudioStream::getParams(PaDeviceIndex device, int channel_count) {
        if (device == -1)
            return {};
        else return {
            .device = device,
            .channelCount = channel_count,
            .sampleFormat = paInt32,
            .suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowInputLatency,
            .hostApiSpecificStreamInfo = nullptr
        };
    }
} // data