//
// Created by sekibanki on 1/10/23.
//

#ifndef MUSICVISUALIZER_PORTAUDIOSTREAM_H
#define MUSICVISUALIZER_PORTAUDIOSTREAM_H

#include <functional>
#include "portaudio.h"
#include "IAudioCallback.h"

    /**
     * A set of parameters to be used with Pa_OpenStream
     */
    struct PortAudioStreamOpenParameters {
        PaStream** stream;
        const PaStreamParameters* inParams;
        const PaStreamParameters* outParams;
        double sampleRate;
        unsigned long framesPerBuffer;
        PaStreamFlags flags;
        void* userData;
    };

namespace mvlizer::data {

    // data

    /**
     * An abstract class that represents a generic PortAudio stream
     *
     */
    class PortAudioStream {
    public:

        /**
         * @constructor
         *
         * @param sampleRate the desired sample rate for the stream. Actual sample rate dependent on device's capabilities.
//         * @param framesPerBuffer the number of frames in a buffer to be passed to the callback
         * @param inDevice The device to be used as the input device
         * @param inChannelCount The number of input channels
         * @param outDevice The device to be used as the output device
         * @param outChannelCount The number of output channels
         */
        PortAudioStream(double sampleRate, unsigned long framesPerBuffer, PaDeviceIndex inDevice,
                        int inChannelCount, PaDeviceIndex outDevice, int outChannelCount,
                        std::shared_ptr<IAudioCallback> callbacks);

        PaStreamCallbackResult callback(
                const int32_t* inputBuffer,
                const int32_t* outputBuffer,
                unsigned long framesPerBuffer,
                const PaStreamCallbackTimeInfo* timeInfo,
                PaStreamCallbackFlags flags
        );

        void finished_callback();

        explicit operator PaStream*();

        virtual ~PortAudioStream() = default;

        /**
         * Gets the parameters to be used with Pa_OpenStream
         *
         * @return a PortAudioStreamOpenParameters struct to be used when opening a stream
         */
        virtual PortAudioStreamOpenParameters GetOpenParams();

    private:

        static PaStreamParameters getParams(PaDeviceIndex device, int channel_count);

        const PaStreamParameters outputParameters;
        const PaStreamParameters inputParameters;

        const unsigned long FramesPerBuffer;
        const double SampleRate;
        PaStream* inner_stream;

        std::shared_ptr<IAudioCallback> callbacks;

    };
}

#endif //MUSICVISUALIZER_PORTAUDIOSTREAM_H
