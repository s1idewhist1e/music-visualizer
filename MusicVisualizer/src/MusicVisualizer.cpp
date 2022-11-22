// MusicVisualizer.cpp : Defines the entry point for the application.
//

#include "MusicVisualizer.h"
#include "Utils/Rendering/Objects/IRenderObject.h"
#include "Utils/Rendering/Objects/VisualizerObject.h"
#include <GLFW/glfw3.h>

int main()
{
	mvlizer::Database data;

	std::shared_ptr<spikeylog::ILogger> logger(new spikeylog::Logger(std::cout, std::cerr));

	data.renderObjects = std::vector<mvlizer::IRenderObject*>{ new mvlizer::VisualizerObject(logger, data) };

#ifndef NDEBUG
	logger->enableLogLevel(spikeylog::LogLevel::DEBUG, 0);
	logger->enableLogLevel(spikeylog::LogLevel::TRACE, 0);
#else
	logger->disableLogLevel(spikeylog::LogLevel::DEBUG, 0);
	logger->disableLogLevel(spikeylog::LogLevel::TRACE, 0);
#endif

	std::thread renderThread(rendering_thread, std::ref(data), logger);
	std::thread calculationThread(update_thread, std::ref(data), logger);

	renderThread.join();
	calculationThread.join();
	return 0;
}

void update_thread(mvlizer::Database& database, std::shared_ptr<spikeylog::ILogger> logger)
{
	unsigned long tick = 0;
	auto prev = std::chrono::high_resolution_clock::now();
	try {
		while (!database.should_close) {
			auto time = prev + std::chrono::milliseconds(10);
			for (mvlizer::IRenderObject* obj : database.renderObjects) {
				obj->update();
			}
			preciseSleepUntil(time);
			auto later = std::chrono::high_resolution_clock::now();
			prev = later;
			database.setUpdateTime(std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(later - time).count());
			tick++;
		}

	}
	catch (std::runtime_error e) {
		logger->fatal((std::ostringstream() << "[UPDATE] " << e.what()).str());
	}

}


void rendering_thread(mvlizer::Database& database, std::shared_ptr<spikeylog::ILogger> logger)
{
	try {
		mvlizer::Renderer renderer(logger, database);
		renderer.createWindow();
		renderer.start();
	}
	catch (std::runtime_error e) {
		logger->fatal((std::ostringstream() << "[RENDERING] " << e.what()).str());
	}

}

// https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
void preciseSleepUntil(std::chrono::time_point<std::chrono::high_resolution_clock> time) {

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