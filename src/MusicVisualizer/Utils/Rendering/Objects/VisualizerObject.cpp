#include "VisualizerObject.h"
#include "Utils/Math/FourierTransforms.h"
#include "Utils/Math/PolygonMath.h"

namespace mvlizer::rendering {
	VisualizerObject::VisualizerObject(std::shared_ptr<spikeylog::ILogger> logger, data::Database& database)
		: logger(logger),
		database(database),
		audioValues()
	{
		for (int i = 0; i < 1000; i++) {
			audioValues.push_back((2 * rand() / (double)RAND_MAX) - 1.0);
		}
	}

	void VisualizerObject::onRender() {

	}

	void VisualizerObject::onUpdate() {
		transformValues = FourierTransforms::discreteFourierTransform(audioValues, 10);
		vertices.clear();
		vertices.reserve(transformValues.size() + 2);
		vertices.push_back({ {-1.0f, -1.0f}, {1.0f, 1.0f, 1.0f} });

		for (int i = 0; i < transformValues.size(); i++) {
			vertices.push_back({
				{
					(2 * (i / (float)(transformValues.size() - 1))) - 1.0f,
					2 * (float)sqrt(transformValues[i].first * transformValues[i].first + transformValues[i].second * transformValues[i].second) - 1.0f // Absolute value of the complex result from the fourier transform
				},
				{
					1.0f,
					rand() / (float)RAND_MAX,
					1.0f
				}
				});
		}
		vertices.push_back({ { 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f} });

		elements.clear();
		elements = math::PolygonMath::triangulate2DPolygon(vertices);
		for (int i = 0; i < audioValues.size(); i++) {
			audioValues[i] = (2 * rand() / (double)RAND_MAX) - 1.0;
		}
	}
}