// MusicVisualizer.cpp : Defines the entry point for the application.
//

#include "MusicVisualizer.h"
#include "Utils/Rendering/Objects/IRenderObject.h"
#include "Utils/Rendering/Objects/VisualizerObject.h"
#include "Utils/Rendering/Objects/DirectDataObject.h"
#include "Utils/Rendering/ContextCreation/GLFWHandler.h"
#include <GLFW/glfw3.h>
namespace mvlizer::app {
		MusicVisualizer* MusicVisualizer::instance = nullptr;
		std::mutex MusicVisualizer::instance_mutex;

		MusicVisualizer* MusicVisualizer::getInstance(int argc, char* argv[]) {
			std::lock_guard<std::mutex> guard(instance_mutex);
			if (instance == nullptr) {
				instance = new MusicVisualizer(argc, argv);
			}

			return instance;
		}

		MusicVisualizer::~MusicVisualizer() {
			//delete instance;
		}

		MusicVisualizer::MusicVisualizer(int argc, char* argv[])
			: logger(new spikeylog::Logger(std::cout, std::cerr))
		{



			database.Init(logger);
		}

		int MusicVisualizer::run() {

#ifndef NDEBUG
			logger->enableLogLevel(spikeylog::LogLevel::DEBUG, 0);
			logger->enableLogLevel(spikeylog::LogLevel::TRACE, 0);
#else
            logger->disableLogLevel(spikeylog::LogLevel::DEBUG, 0);
            logger->disableLogLevel(spikeylog::LogLevel::TRACE, 0);
#endif
            database.renderObjects = std::vector<mvlizer::rendering::IRenderObject*>{ new mvlizer::rendering::DirectDataObject(logger, database) };
            database.update_delay = 16600;
            logger->trace("Creating rendering thread...");
            std::thread renderThread(&MusicVisualizer::rendering_thread, this);
			logger->trace("Creating calculation thread...");
			std::thread calculationThread(&MusicVisualizer::update_thread, this);

			//update_thread();

			renderThread.join();
			calculationThread.join();
			return 0;
		}

		void MusicVisualizer::update_thread()
		{
			logger->trace("Update thread started");
			unsigned long tick = 0;
			try {
				auto prev = std::chrono::high_resolution_clock::now();
				while (!database.should_close) {
					auto time = prev + std::chrono::microseconds(database.update_delay);
					database.update();
					preciseSleepUntil(time);
					auto later = std::chrono::high_resolution_clock::now();
					prev = later;
					database.setUpdateTime(std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(later - time).count());
					tick++;
				}

			}
			catch (const std::runtime_error& e) {
				std::ostringstream s;
				s << "[UPDATE] " << e.what();
				logger->fatal(s.str());
			}

		}



		void MusicVisualizer::rendering_thread()
		{
			logger->trace("Rendering thread started");
			try {
				mvlizer::rendering::Renderer renderer(logger, database);
				renderer.createWindow();
				renderer.start();
			}
			catch (const std::runtime_error& e) {
				std::ostringstream s;
				s << "[RENDERING] " << e.what();
				logger->fatal(s.str());
                throw e;
			}

		}

		// https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
		void MusicVisualizer::preciseSleepUntil(const std::chrono::time_point<std::chrono::high_resolution_clock> &time) {

			auto now = std::chrono::high_resolution_clock::now();
			double seconds = std::chrono::duration_cast<std::chrono::duration<double>>(time - now).count();

			using namespace std;
			using namespace std::chrono;

			static double estimate = 5e-3;
			static double mean = 5e-3;
			static double m2 = 0;
			static int64_t count = 1;

			while (seconds > estimate) {
				auto start = high_resolution_clock::now();
				this_thread::sleep_for(milliseconds(1));
				auto end = high_resolution_clock::now();

				double observed = (end - start).count() / 1e9;
				seconds -= observed;

				++count;
				double delta = observed - mean;
				mean += delta / count;
				m2 += delta * (observed - mean);
				double stddev = sqrt(m2 / (count - 1));
				estimate = mean + stddev;
			}

			// spin lock
			auto start = high_resolution_clock::now();
			while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
		}
	}
