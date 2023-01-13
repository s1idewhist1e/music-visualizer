//
// Created by sekibanki on 1/10/23.
//

#ifndef MUSICVISUALIZER_PORTAUDIOHANDLER_H
#define MUSICVISUALIZER_PORTAUDIOHANDLER_H

#include <spikeylog.h>
#include <portaudio.h>

#include <memory>
#include <vector>
#include "PortAudioStream.h"

namespace mvlizer::data {

    class PortAudioHandler {
    public:

        /**
         *
         * @param logger
         */
        explicit PortAudioHandler(std::shared_ptr<spikeylog::ILogger> logger);

        virtual ~PortAudioHandler();

        /**
         * Gets a list of audio devices to use when opening a stream
         *
         * @param desiredSampleRate the sample rate to query for
         * @return a vector of devices that match the sample rate
         */
        std::vector<PaDeviceInfo> GetAudioDevices();

        /**
         * Adds a stream to PortAudio and starts it
         *
         * @param stream the stream object from which to add the stream
         */
        void AddAudioStream(std::shared_ptr<PortAudioStream> stream);

    private:

        static int
        callback(
                const void* input_buffer,
                void* output_buffer,
                unsigned long framesPerBuffer,
                const PaStreamCallbackTimeInfo* timeInfo,
                PaStreamCallbackFlags statusFlags,
                void* data
        );

        static void finished_callback(void* data);

        std::shared_ptr<spikeylog::ILogger> logger;
    };

    /**
     * An exception for audio errors
     */
    class audio_error : public std::runtime_error {
    public:
        explicit audio_error(const std::string& str) : std::runtime_error(str) {};
    };

} // data

#endif //MUSICVISUALIZER_PORTAUDIOHANDLER_H
