#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <atomic>
#include "Utils/Rendering/Objects/IRenderObject.h"

namespace mvlizer {
	class Database {
	public:
		Database();
		std::vector<IRenderObject*> renderObjects;
		void setUpdateTime(double time);
		double getUpdateTime();
		void setRenderTime(double time);
		double getRenderTime();
		std::atomic_bool should_close;
		~Database();
	private:
		double updateTime;
		std::shared_mutex update_mut;
		double renderTime;
		std::shared_mutex render_mut;
	};

}
#endif