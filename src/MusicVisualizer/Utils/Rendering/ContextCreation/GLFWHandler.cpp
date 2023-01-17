//
// Created by yukari on 1/9/23.
//

#include <cstring>
#include "GLFWHandler.h"


#define GLFW_HANDLER_IS_INIT() \
		if(!is_init) { \
			throw std::runtime_error("GLFW is not init: " __FILE__ ", line " STR_LINE_);\
		}
#define GLFW_HANDLER_IS_INIT_THREAD()	\
		if (init_thread_id != std::this_thread::get_id()) { \
			throw std::runtime_error("Cannot call GLFW functions at " __FILE__ ":" xstr_(__LINE__) " from threads other then the primary rendering thread."); \
		} \


namespace mvlizer::rendering {

    GLFWHandler* GLFWHandler::instance = nullptr;
    std::mutex GLFWHandler::instance_mtx;

    GLFWHandler* rendering::GLFWHandler::GetInstance(std::shared_ptr<spikeylog::ILogger> in_logger) {

        std::lock_guard<std::mutex> guard(instance_mtx);

        if (instance == nullptr) {
            instance = new GLFWHandler(in_logger);
        }


        return instance;
    }

    Context* GLFWHandler::CreateWindow(const contextCreationArgs& args) {

        GLFW_HANDLER_IS_INIT();
        GLFW_HANDLER_IS_INIT_THREAD();

        if (window != nullptr) {
            throw std::runtime_error("Window already exists. Cannot create multiple windows!");
        }

        logger->trace("Creating GLFW window...");

        for (const auto& hint : args.hints) {
            glfwWindowHint(hint.Key, hint.Value);
        }

        auto monitor = args.fullscreen ? glfwGetPrimaryMonitor() : nullptr;

        auto win = glfwCreateWindow(args.width, args.height, args.title.c_str(), monitor, nullptr);
        if (!win) {
            throw std::runtime_error("GLFW Window creation failed!");
        }
        window = new Context(win);
        return window;
    }

    void GLFWHandler::DestroyWindow() {

        GLFW_HANDLER_IS_INIT();
        GLFW_HANDLER_IS_INIT_THREAD();

        if (window == nullptr) {
            throw std::runtime_error("No window to destroy!");
        }
        logger->trace("Destroying GLFW Window");
        glfwDestroyWindow(window->window);
        delete window;
        window = nullptr;
    }

    void GLFWHandler::glfwErrorCallback(int error_code, const char* description) {

    }

    GLFWHandler::GLFWHandler(std::shared_ptr<spikeylog::ILogger> in_logger)
            : logger{std::move(in_logger)},
              init_thread_id{std::this_thread::get_id()} {

        if (!glfwInit()) {

            char desc[512];
            const char* ptr = desc;
            glfwGetError(&ptr);

            std::ostringstream str;
            str << "Error while initializing glfw: " << ptr;

            throw std::runtime_error(str.str());
        } else {
            logger->trace("GLFW successfully initialized");
        }

        is_init = true;




    }

    void GLFWHandler::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    }
}
