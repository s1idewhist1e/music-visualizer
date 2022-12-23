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

    struct contextHint {
        int Key;
        int Value;
    };

    struct contextCreationArgs {
        int width, height;
        bool fullscreen = false;
        std::string title;
        std::list<contextHint> hints;
    };

    class GLFWHandler {
	public:
        // Initializes GLFW
		static void Init(const std::shared_ptr<spikeylog::ILogger>&);

        // Terminates GLFW
        static void Terminate();

        // Creates a GLFWwindow and binds it to a context to be used for rendering
		static Context* createContext(const contextCreationArgs &args);

        // Destroys the context and closes the GLFWwindow associated with it
        static void destroyContext(Context*& ctx);

        // The callback for GLFW to use on keypress
        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // The callback for GLFW to use when there's an error
        static void glfwErrorCallback(int error, const char* description);

        // Loop through each context and do something
        static void forEachContext(std::function<void(Context*&, const GLFWwindow*)>);

    private:
        static std::shared_ptr<spikeylog::ILogger> logger;
        static std::atomic_bool is_init;
        static std::thread::id init_thread_id;
        static std::map<GLFWwindow*, Context*> contexts;
	};


}

#endif