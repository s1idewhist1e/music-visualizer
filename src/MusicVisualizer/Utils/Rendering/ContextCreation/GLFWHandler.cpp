//#include "GLFWHandler.h"
//
//#include <utility>
//
//namespace mvlizer::rendering {
//
////	std::thread::id GLFWHandler::init_thread_id;
//	std::shared_ptr<spikeylog::ILogger> GLFWHandler::logger;
////	std::atomic_bool GLFWHandler::is_init = false;
//	std::map<GLFWwindow*, Context*> GLFWHandler::contexts;
//
//
//	GLFWHandler::GLFWHandler(std::shared_ptr<spikeylog::ILogger> _logger) {
//        GLFWHandler::logger = _logger;
//		logger->trace("Initializing GLFW");
//
//            if (!glfwInit()) {
//                throw std::runtime_error("Failed to initialize GLFW!");
//            }
//            logger->trace("GLFW successfully initialized");
//
//            logger->trace("Registering GLFW error callback");
//            glfwSetErrorCallback(glfwErrorCallback);
//
//            is_init = true;
//            init_thread_id = std::this_thread::get_id();
//
//
//	}
//
//    void GLFWHandler::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//        Context* ctx = contexts.at(window);
//        ctx->glfwKeyCallback(key, scancode, action, mods);
//    }
//
//    void GLFWHandler::glfwErrorCallback(int error, const char *description) {
//        switch (error) {
//            default:
//                std::ostringstream stream;
//                stream << "GLFW Error " << error << ":\n\t" << description;
//                logger->error(stream.str());
//        }
//    }
//
//    Context *GLFWHandler::createContext(const contextCreationArgs &args) {
//        GLFW_HANDLER_IS_INIT();
//        GLFW_HANDLER_IS_INIT_THREAD();
//        for (const auto& arg : args.hints) {
//            glfwWindowHint(arg.Key, arg.Value);
//        }
//        GLFWwindow* window = glfwCreateWindow(args.width, args.height, args.title.c_str(), nullptr, nullptr);
//        auto* ctx = new Context(window);
//
//        if (!contexts.emplace(window, ctx).second) {
//            logger->warn("Could not emplace new context into map of contexts: Likely this window already exists somehow.");
//        }
//
//
//        return ctx;
//
//    }
//
//    void GLFWHandler::Terminate() {
//        glfwTerminate();
//
//        glfwSetErrorCallback(nullptr);
//
//        for (auto ctx : contexts) {
//            delete ctx.second;
//        }
//
//        contexts.clear();
//        is_init = false;
//    }
//
//    void GLFWHandler::destroyContext(Context*& ctx) {
//        delete ctx;
//        ctx = nullptr;
//    }
//
//    void GLFWHandler::forEachContext(std::function<void(Context*&, const GLFWwindow*)> predicate) {
//
//    }
//
//    GLFWHandler* GLFWHandler::GetInstance(std::shared_ptr<spikeylog::ILogger>) {
//        if ()
//    }
//}