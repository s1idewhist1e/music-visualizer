#include "MusicVisualizer/MusicVisualizer.h"

int main(int argc, char* argv[]) {
	try {
		auto instance = mvlizer::app::MusicVisualizer::getInstance(argc, argv);
		return instance->run();
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
		return 1;
	}
}