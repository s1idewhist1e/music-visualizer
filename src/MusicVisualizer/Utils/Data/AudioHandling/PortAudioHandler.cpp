//
// Created by sekibanki on 1/10/23.
//

#include <sstream>
#include "PortAudioHandler.h"

namespace mvlizer::data {
    PortAudioHandler::~PortAudioHandler() noexcept(false) {
        auto err = Pa_Terminate();
        if (err != paNoError) {
            std::ostringstream throw_stream;
            throw_stream << "Error terminating PortAudio \n\t"
                         << Pa_GetErrorText(err);
            throw audio_error(throw_stream.str());
        }

    }

    int PortAudioHandler::callback(const void* input_buffer,
                                   void* output_buffer,
                                   unsigned long framesPerBuffer,
                                   const PaStreamCallbackTimeInfo* timeInfo,
                                   PaStreamCallbackFlags statusFlags,
                                   void* data) {
        auto streamData = (PortAudioStream*) data;
        return streamData->callback((float*) input_buffer, (float*) output_buffer, framesPerBuffer, timeInfo,
                                    statusFlags);
    }

    void PortAudioHandler::AddAudioStream(std::shared_ptr<PortAudioStream> stream) {
        logger->trace("Starting audio stream in portaudio...");

        auto params = stream->GetOpenParams();

        auto err = Pa_OpenStream(
                params.stream,
                params.inParams,
                params.outParams,
                params.sampleRate,
                params.framesPerBuffer,
                params.flags,
                PortAudioHandler::callback,
                params.userData
        );

        if (err != paNoError) {
            std::ostringstream error_message;
            error_message << "Error while opening PortAudio stream: \n\t" <<
                          Pa_GetErrorText(err);
            throw audio_error(error_message.str());
        }

        Pa_SetStreamFinishedCallback(*params.stream, finished_callback);

        Pa_StartStream(*params.stream);
    }

    std::vector<PaDeviceInfo> PortAudioHandler::GetAudioDevices() {
        std::vector<PaDeviceInfo> info;

        int num_devices = Pa_GetDeviceCount();

        if (num_devices == paNotInitialized) {
            throw audio_error("PortAudio not initialized!");
        }

        for (int i = 0; i < num_devices; i++) {
            info.push_back(*Pa_GetDeviceInfo(i));
        }

        return info;
    }

    PortAudioHandler::PortAudioHandler(std::shared_ptr<spikeylog::ILogger> logger)
            : logger{std::move(logger)} {
        auto err = Pa_Initialize();
        if (err != paNoError) {
            std::ostringstream throw_string;
            throw_string << "Error while initializing PortAudio: \n\t"
                         << Pa_GetErrorText(err);
            throw audio_error(throw_string.str());
        }

        auto num_devices = Pa_GetDeviceCount();
        if (num_devices <= 0) {
            throw audio_error("No audio devices! If building from source please make sure you have the appropriate audio libraries! (they vary by system)");
        }

//            std::cout << Pa_GetErrorText(err) << " \n\t >>" << err << std::endl;

    }

    void PortAudioHandler::finished_callback(void* data) {
        auto cast_data = (PortAudioStream*)data;
        return cast_data->finished_callback();
    }

} // mvlizer::data