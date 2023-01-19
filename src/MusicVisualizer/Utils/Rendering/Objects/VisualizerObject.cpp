#include "VisualizerObject.h"
#include "Utils/Math/FourierTransforms.h"
#include "Utils/Math/PolygonMath.h"

namespace mvlizer::rendering {
    VisualizerObject::VisualizerObject(std::shared_ptr<spikeylog::ILogger> logger, data::Database& database)
            : BaseRenderObject(),
              logger(logger),
              database(database),
              handler(logger),
              callback{std::make_shared<data::AudioCallbacks>(512, 512)} {
        auto stream = std::make_shared<data::PortAudioStream>(Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->defaultSampleRate, 512, Pa_GetDefaultInputDevice(), 1, -1, 0,
                                                              callback);
        handler.AddAudioStream(stream);

    }

    void VisualizerObject::onRender() {

    }

    void VisualizerObject::onUpdate() {
        auto data  = callback->GetAudioData();
        transformValues = FourierTransforms<std::deque<float>::iterator>::discreteFourierTransform(data.begin(), data.end(), 1);
        vertices.clear();
        elements.clear();
        elements.reserve(transformValues.size() * 6);
        vertices.reserve(transformValues.size() * 2 + 2);
        vertices.push_back({{-1.0f, 0.0f},
                            {1.0f,  1.0f, 1.0f}});

        for (int i = 0; i < transformValues.size(); i++) {
            vertices.push_back({
                                       {
                                               (2 * (i / (float) (transformValues.size() - 1))) - 1.0f,
                                               (float) transformValues[i].first // Absolute value of the complex result from the fourier transform
                                       },
                                       {
                                               1.0f,
                                               1.0f,
                                               1.0f
                                       }
                               });
        }
        vertices.push_back({{1.0f, -1.0f},
                            {1.0f, 1.0f, 1.0f}});

        for (int i = transformValues.size() - 1; i >= 0; i--) {
            vertices.push_back({
                                       {
                                               (2 * (i / (float) (transformValues.size() - 1))) - 1.0f,
                                               (float) transformValues[i].second
                                       },
                                       {
                                               1.0f,
                                               1.0f,
                                               1.0f
                                       }
                               });
        }

        elements.clear();
        elements = math::PolygonMath::triangulate2DPolygon(vertices);
    }
}