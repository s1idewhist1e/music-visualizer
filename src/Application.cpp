#include "MusicVisualizer/MusicVisualizer.h"

int main(int argc, char* argv[]) {
	try {
		return mvlizer::app::Start(argc, argv);
	}
	catch (std::runtime_error err) {
		std::cout << err.what() << std::endl;
		return -1;
	}
}