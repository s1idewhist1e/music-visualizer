#include "VisualizerObject.h"
#include "Utils/Math/FourierTransforms.h"
#include "Utils/Math/PolygonMath.h"

namespace mvlizer {
	VisualizerObject::VisualizerObject(std::shared_ptr<spikeylog::ILogger> logger, Database& database)
		: logger(logger),
		database(database),
		audioValues()
	{
		for (int i = 0; i < 20000; i++) {
			audioValues.push_back((2 * rand() / (double)RAND_MAX) - 1.0);
		}
	}

	void VisualizerObject::onRender() {
		
	}

	void VisualizerObject::onUpdate() {
		transformValues = FourierTransforms::discreteFourierTransform(audioValues, 2);
		vertices.clear();
		vertices.reserve(transformValues.size() + 2);
		vertices.push_back({ {-1.0f, -1.0f}, {1.0f, 1.0f, 1.0f} });

		for (int i = 0; i < transformValues.size(); i++) {
			vertices.push_back({ {(2 * (i / (float)(transformValues.size() - 1))) - 1.0f, 2 * (float)sqrt(transformValues[i].first * transformValues[i].first + transformValues[i].second * transformValues[i].second) - 1.0f}, {1.0f, 1.0f, 1.0f} });
		}
		vertices.push_back({ { 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f} });

		elements.clear();
		elements = PolygonMath::triangulate2DPolygon(vertices);
		logger->debug("object updated!");
		for (int i = 0; i < audioValues.size(); i++) {
			audioValues[i] = (2 * rand() / (double)RAND_MAX) - 1.0;
		}
	}
}