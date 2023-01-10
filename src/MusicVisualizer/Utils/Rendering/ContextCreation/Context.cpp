
#include "Context.h"

namespace mvlizer::rendering {
    void Context::glfwKeyCallback(int key, int scancode, int action, int mods) {

    }

    Context::Context(GLFWwindow* win)
        : window{win} {

    }
}

