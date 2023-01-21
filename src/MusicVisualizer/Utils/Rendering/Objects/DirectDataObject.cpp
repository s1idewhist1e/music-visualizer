//
// Created by sekibanki on 1/19/23.
//

#include "DirectDataObject.h"

namespace mvlizer {
    namespace rendering {
        DirectDataObject::DirectDataObject(std::shared_ptr<spikeylog::ILogger> logger, data::Database& database)
                : BaseRenderObject(),
                  _logger(logger),
                  _data(database),
                  handler(logger),
                  callbacks{std::make_shared<data::AudioCallbacks>(4096, 256)} {

            auto stream = std::make_shared<data::PortAudioStream>(
                    Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->defaultSampleRate,
                            256,
                            Pa_GetDefaultInputDevice(),
                            2,
                            -1,
                            0,
                            callbacks
                            );
            handler.AddAudioStream(stream);

        }

        void DirectDataObject::onUpdate() {
            auto data = callbacks->GetAudioData();
            vertices.clear();
            vertices.reserve(data.size());
            elements.clear();
            elements.reserve(data.size() * 3);

            for (int i = 0; i < data.size(); i+=1 ) {
                vertices.push_back({{
                    (-2 * (i / (float) (data.size() + 1))) + 1.0f,
                    data[i]
                    },
                                    {
                    1.0f,
                    1.0,
                    1.0
                }});

                if ( i > 2) {
                    elements.push_back(i - 1);
                    elements.push_back(i - 2);
                    elements.push_back(i - 3);
                }
            }

            smooth(vertices, elements, 128);

        }

        void DirectDataObject::smooth(std::vector<Vertex>& list, std::vector<GLint>& elems, int step) {
            size_t size = list.size();
            for (auto iter = list.begin(); iter != list.end() - step; iter++) {
                double sum = 0;
                for (int i = 0; i < step; i++) {
                    sum += (iter + i)->pos.y;
                }
                sum /= step;
                iter->pos.y = sum;
                iter->pos.x = (((double)size / (size - step)) * iter->pos.x) - (((double) size / (size - step)) - 1);


            }

            list.resize(list.size() - (step));
            elems.resize(elems.size() - (step * 3));
        }
    } // mvlizer
} // rendering