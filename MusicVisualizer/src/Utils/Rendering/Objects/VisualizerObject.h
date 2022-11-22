#pragma once
#ifndef VISUALIZEROBJECT_H
#define VISUALIZEROBJECT_H

#include "BaseRenderObject.h"
#include "Utils/Data/Database.h"
#include <vector>
#include <memory>

namespace mvlizer {
	class VisualizerObject : public BaseRenderObject {
	public:
		VisualizerObject(std::shared_ptr<spikeylog::ILogger> logger, Database& database);
		void onRender();
		void onUpdate();
	private:
		std::vector<double> audioValues;
		std::vector<std::pair<double, double>> transformValues;
		std::shared_ptr<spikeylog::ILogger> logger;
		Database& database;
		void updateAudioValues();
	};
}
#endif