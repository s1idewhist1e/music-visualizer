#pragma once
#ifndef MUSICVISUALIZER_H
#define MUSICVISUALIZER_H

// includes:
#include "Utils/Rendering/Renderer.h"
#include "Utils/Math/FourierTransforms.h"
#include "Utils/Data/Database.h"
#include <spikeylog.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <sstream>
namespace mvlizer {
	namespace app {
		int Start(int argc, char* argv[]);
	}
}

void update_thread(mvlizer::Database& database, std::shared_ptr<spikeylog::ILogger> logger);

void rendering_thread(mvlizer::Database& database, std::shared_ptr<spikeylog::ILogger> logger);

void preciseSleepUntil(std::chrono::time_point<std::chrono::high_resolution_clock> time);
#endif