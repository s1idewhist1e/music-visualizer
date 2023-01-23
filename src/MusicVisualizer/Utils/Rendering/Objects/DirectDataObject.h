//
// Created by sekibanki on 1/19/23.
//

#ifndef MUSICVISUALIZER_DIRECTDATAOBJECT_H
#define MUSICVISUALIZER_DIRECTDATAOBJECT_H

#include <memory>
#include "BaseRenderObject.h"
#include "Utils/Data/Database.h"
#include "Utils/Data/AudioHandling/PortAudioHandler.h"
#include "Utils/Data/AudioCallbacks.h"

namespace mvlizer {
    namespace rendering {

        class DirectDataObject : public BaseRenderObject {
        public:
            DirectDataObject(std::shared_ptr<spikeylog::ILogger> logger, data::Database& data);

            void onUpdate() override;
            void onRender() override {};

        private:

            static void smooth(std::deque<float>& data, int step);

            data::Database& _data;
            std::shared_ptr<spikeylog::ILogger> _logger;

            data::PortAudioHandler handler;
            std::shared_ptr<data::AudioCallbacks> callbacks;
        };

    } // mvlizer
} // rendering

#endif //MUSICVISUALIZER_DIRECTDATAOBJECT_H
