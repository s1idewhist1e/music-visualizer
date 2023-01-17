#pragma once
#ifndef GLFW_CONTEXT_H
#define GLFW_CONTEXT_H

#include <GLFW/glfw3.h>

namespace mvlizer::rendering {
	class Context {
    public:
        explicit Context(GLFWwindow*);
        void glfwKeyCallback(int key, int scancode, int action, int mods);

        GLFWwindow* window = nullptr;
	};
}

#endif