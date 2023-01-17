//
// Created by yukari on 1/9/23.
//

#include <cstring>
#include "GLFWHandler.h"

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

    std::atomic<std::shared_ptr<Context>> GLFWHandler::CreateWindow(const contextCreationArgs& args) {

        if (window.load() != nullptr) {
            throw std::runtime_error("Window already exists. Cannot create multiple windows!");
        }

        logger->trace("Creating GLFW window...");

        for (const auto& hint : args.hints) {
            glfwWindowHint(hint.Key, hint.Value);
        }
        auto win = glfwCreateWindow(args.width, args.height, args.title.c_str(), nullptr, nullptr);
        if (!win) {
            throw std::runtime_error("GLFW Window creation failed!");
        }
        window = std::make_shared<Context>(win);
        return window.load();
    }

    void GLFWHandler::DestroyWindow() {
        if (window.load() == nullptr) {
            throw std::runtime_error("No window to destroy!");
        }
        logger->trace("Destroying GLFW Window");
        glfwDestroyWindow(window.load()->window);
        window.load() = nullptr;
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




    }

    void GLFWHandler::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    }
}
