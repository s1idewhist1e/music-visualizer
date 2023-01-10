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
#include <sstream>
#include <list>
#include <functional>
#include <shared_mutex>
#include <unordered_set>

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

namespace mvlizer::rendering {

    struct contextHint {
        int Key;
        int Value;
    };

    struct contextCreationArgs {
        int width = 600, height = 400;
        bool fullscreen = false;
        std::string title;
        std::list<contextHint> hints;
    };

    class GLFWHandler {
	public:
        static GLFWHandler* GetInstance(std::shared_ptr<spikeylog::ILogger>);

        std::atomic<std::shared_ptr<Context>> CreateWindow(const contextCreationArgs&);
        void DestroyWindow();

        std::atomic<std::shared_ptr<Context>> Window;

    private:
        static void glfwErrorCallback(int error_code, const char* description);
        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static std::mutex instance_mtx;
        static GLFWHandler* instance;
        explicit GLFWHandler(std::shared_ptr<spikeylog::ILogger>);

        static std::shared_ptr<spikeylog::ILogger> logger;

        std::thread::id init_thread_id;
        std::atomic_bool is_init = false;
    };


}

#endif