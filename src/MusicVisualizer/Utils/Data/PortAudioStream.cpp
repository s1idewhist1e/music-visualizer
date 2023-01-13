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

                  inputParameters{
                          inDevice,
                          inChannelCount,
                          paFloat32,
                          Pa_GetDeviceInfo(inDevice)->defaultLowInputLatency,
                          nullptr
                  },
                  outputParameters{
                          outDevice,
                          outChannelCount,
                          paFloat32,
                          Pa_GetDeviceInfo(outDevice)->defaultLowOutputLatency,
                          nullptr
                  } {

        }

        PortAudioStreamOpenParameters PortAudioStream::GetOpenParams() {
            return {
                    .stream             = &inner_stream,
                    .inParams           = &inputParameters,
                    .outParams          = &outputParameters,
                    .sampleRate         = SampleRate,
                    .framesPerBuffer    = FramesPerBuffer,
                    .flags              = paNoFlag,
                    .userData           = this
            };
        }

        PaStreamCallbackResult
        PortAudioStream::callback(const float* inputBuffer, const float* outputBuffer, unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags flags) {
            return callbacks->OnCall(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, flags);
        }

    void PortAudioStream::finished_callback() {
            callbacks->OnFinish();
    }
} // data