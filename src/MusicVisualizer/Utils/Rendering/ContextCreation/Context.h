#pragma once
#ifndef GLFW_CONTEXT_H
#define GLFW_CONTEXT_H

namespace mvlizer {
	class Context {
    public:
        void glfwKeyCallback(int key, int scancode, int action, int mods);
        GLFWwindow* window;
	};
}

#endif