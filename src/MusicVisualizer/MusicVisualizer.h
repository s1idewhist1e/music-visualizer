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

	// Important const variables
	constexpr auto WINDOW_TITLE = "MusicVisualizer";
	constexpr auto GL_VERSION_MAJOR = 3;

	namespace app {
		class MusicVisualizer {
		public:
            static MusicVisualizer* getInstance(int argc, char* argv[]);
            virtual ~MusicVisualizer();
            static void preciseSleepUntil(const std::chrono::time_point<std::chrono::high_resolution_clock> &time);
            int run();
            MusicVisualizer(MusicVisualizer const& previous) = delete;
        protected:
            mvlizer::Database database;

			std::shared_ptr<spikeylog::ILogger> logger;

			static MusicVisualizer* instance;
            MusicVisualizer(int argc, char* argv[]);
			void update_thread();
			void rendering_thread();

			static std::mutex instance_mutex;

		
		};
	}
}
#endif