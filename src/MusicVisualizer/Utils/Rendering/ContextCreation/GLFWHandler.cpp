#include "GLFWHandler.h"

#include <utility>

namespace mvlizer {

	std::thread::id GLFWHandler::init_thread_id;
	std::shared_ptr<spikeylog::ILogger> GLFWHandler::logger;
	bool GLFWHandler::is_init = false;
	std::map<GLFWwindow*, Context*> GLFWHandler::contexts;


	void GLFWHandler::Init(const std::shared_ptr<spikeylog::ILogger>& _logger) {
		GLFWHandler::logger = _logger;
		GLFWHandler::logger->trace("Initializing GLFW");
		if (is_init) {
			GLFWHandler::logger->warn("GLFW is already initialized. Cannot reinitialize. Continuing...");
			return;
		}
		GLFWHandler::init_thread_id = std::this_thread::get_id();

		is_init = true;

	}
}