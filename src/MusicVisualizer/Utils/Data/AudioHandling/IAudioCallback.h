//
// Created by sekibanki on 1/11/23.
//

#ifndef MUSICVISUALIZER_IAUDIOCALLBACK_H
#define MUSICVISUALIZER_IAUDIOCALLBACK_H

#include "portaudio.h"

namespace mvlizer::data {

        class IAudioCallback {
        public:
            /**
             * The main callback method for PortAudio
             *
             * @param inputBuffer
             * @param outputBuffer
             * @param framesPerBuffer
             * @param timeInfo
             * @param flags
             * @return
             */
            virtual PaStreamCallbackResult OnCall(
                    const int32_t* inputBuffer,
                    const int32_t* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags flags
                    ) = 0;

            /**
             *
             */
            virtual void OnFinish() = 0;
        };

    } // data

#endif //MUSICVISUALIZER_IAUDIOCALLBACK_H
