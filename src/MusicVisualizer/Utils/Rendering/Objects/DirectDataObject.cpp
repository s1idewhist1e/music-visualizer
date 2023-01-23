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
                  callbacks{std::make_shared<data::AudioCallbacks>(441, 256)} {

            auto stream = std::make_shared<data::PortAudioStream>(
                    Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->defaultSampleRate,
                            1,
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
            auto data_l = data.first;
            auto data_r = data.second;
            vertices.clear();
            vertices.reserve(data_l.size() + data_r.size());
            elements.clear();
            elements.reserve((data_l.size() + data_r.size()) * 2);

            auto size_l = data_l.size();
            auto size_r = data_r.size();

            int division = size_l;

            for (int i = 0; i < data_l.size(); i+= size_l / division) {
                vertices.push_back({{
                                            (-2 * (i / (float) (data_l.size() - 1))) + 1.0f,
                                            (data_l[i])
                    },
                                    {
                    1.0f,
                                            0.0,
                    0.0
                }});

                elements.push_back(i / (size_l / division));
                if (i != 0)
                    elements.push_back(i / (size_l / division));
//                if ( i > 2) {
//                    elements.push_back(i - 1);
//                    elements.push_back(i - 2);
//                    elements.push_back(i - 3);
//                }
            }

            elements.pop_back();

            auto offset = vertices.size();

            for (int i = 0; i < data_r.size(); i+= size_r / division
                    ) {
                vertices.push_back({{
                                            (-2 * (i / (float) (data_r.size() - 1))) + 1.0f,
                                            (data_r[i])
                                    },
                                    {
                                            0.0f,
                                            0.0,
                                            1.0
                                    }});

                elements.push_back(i / (size_r / division) + offset);
                if (i != 0)
                    elements.push_back(i / (size_r / division) + offset);
//                if ( i > 2) {
//                    elements.push_back(i - 1);
//                    elements.push_back(i - 2);
//                    elements.push_back(i - 3);
//                }
            }

            elements.pop_back();

//            smooth(vertices, elements, 128);

        }

        // TODO: make this work
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