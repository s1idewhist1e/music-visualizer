#include "GLFWHandler.h"

#include <utility>

namespace mvlizer {

	std::thread::id GLFWHandler::init_thread_id;
	std::shared_ptr<spikeylog::ILogger> GLFWHandler::logger;
	std::atomic_bool GLFWHandler::is_init = false;
	std::map<GLFWwindow*, Context*> GLFWHandler::contexts;


	void GLFWHandler::Init(const std::shared_ptr<spikeylog::ILogger>& _logger) {
		GLFWHandler::logger = _logger;
		logger->trace("Initializing GLFW");
		if (is_init) {
			logger->warn("GLFW is already initialized. Cannot reinitialize. Continuing...");
			return;
		}
		init_thread_id = std::this_thread::get_id();

		is_init = true;

	}

    void GLFWHandler::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        Context* ctx = contexts.at(window);
        ctx->glfwKeyCallback(key, scancode, action, mods);
    }
}