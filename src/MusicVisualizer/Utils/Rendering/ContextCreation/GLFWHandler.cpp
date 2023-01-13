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
        return std::atomic<std::shared_ptr<Context>>();
    }

    void GLFWHandler::DestroyWindow() {

    }

    void GLFWHandler::glfwErrorCallback(int error_code, const char* description) {

    }

    GLFWHandler::GLFWHandler(std::shared_ptr<spikeylog::ILogger> in_logger)
            : logger{in_logger},
              init_thread_id{std::this_thread::get_id()} {


        int err = glfwInit();
        if (err != GLFW_NO_ERROR) {

            char desc[512];

            const char* ptr = &desc;

            glfwGetError(&desc);


            std::ostringstream str;
            str << "Error while initializing glfw: " << desc;

            throw std::runtime_error(str.str());
        } else {
            logger->trace("GLFW successfully initialized");
        }




    }

    void GLFWHandler::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    }
}
