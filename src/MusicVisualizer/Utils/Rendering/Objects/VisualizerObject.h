#pragma once
#ifndef VISUALIZEROBJECT_H
#define VISUALIZEROBJECT_H

#include "BaseRenderObject.h"
#include "Utils/Data/Database.h"
#include "Utils/Data/AudioHandling/PortAudioHandler.h"
#include "Utils/Data/AudioCallbacks.h"
#include <vector>
#include <memory>

namespace mvlizer::rendering {
	class VisualizerObject : public BaseRenderObject {
	public:
		VisualizerObject(std::shared_ptr<spikeylog::ILogger> logger, data::Database& database);
		void onRender() override;
		void onUpdate() override;
	private:
		std::vector<std::pair<double, double>> transformValues;
		std::shared_ptr<spikeylog::ILogger> logger;
		data::Database& database;

        data::PortAudioHandler handler;
        std::shared_ptr<data::AudioCallbacks> callback;
	};
}
#endif