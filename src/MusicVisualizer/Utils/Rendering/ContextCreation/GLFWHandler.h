#pragma once
#ifndef GLFW_HANDLER_H
#define GLFW_HANDLER_H


#include <GLFW/glfw3.h>
#include "Context.h"
#include <map>
#include <thread>
#include <memory>
#include <stdexcept>
#include <spikeylog.h>

#define str_(a) #a
#define xstr_(a) str_(a)
#define STR_LINE_ xstr_(__LINE__)
#define GLFW_HANDLER_IS_INIT() \
		if(!mvlizer::GLFWHandler::is_init) { \
			throw std::runtime_error("GLFW is not init: " __FILE__ ", line " STR_LINE_);\
		}
#define GLFW_HANDLER_IS_INIT_THREAD()	\
		if (mvlizer::GLFWHandler::init_thread_id != std::this_thread::get_id()) { \
			throw std::runtime_error("Cannot call GLFW functions at " __FILE__ ":" xstr_(__LINE__) " from threads other then the primary rendering thread."); \
		} \

namespace mvlizer {

	struct ContextCreationArgs {
		
	};

	class GLFWHandler {
	public:
		static void Init(const std::shared_ptr<spikeylog::ILogger>&);
		static Context* createContext(const ContextCreationArgs&);
		static std::thread::id init_thread_id;
		static bool is_init;
		static std::shared_ptr<spikeylog::ILogger> logger;
		static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void glfwErrorCallback(int error, const char* description);
	private:
		static std::map<GLFWwindow*, Context*> contexts;
	};


}

#endif