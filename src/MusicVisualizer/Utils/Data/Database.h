#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <memory>
#include "Utils/Rendering/Objects/IRenderObject.h"

namespace mvlizer {
	class Database {
	public:
		Database();

		void Init(std::shared_ptr<spikeylog::ILogger> logger);

		std::shared_ptr<spikeylog::ILogger> logger;

		std::vector<IRenderObject*> renderObjects;
		virtual void setUpdateTime(double time);
		virtual double getUpdateTime();
		virtual void setRenderTime(double time);
		virtual double getRenderTime();
		std::atomic_bool should_close;
		std::atomic_int update_delay;

		virtual void update();

		virtual ~Database();
	private:
		double updateTime;
		std::shared_mutex update_mut;
		double renderTime;
		std::shared_mutex render_mut;
	};

}
#endif