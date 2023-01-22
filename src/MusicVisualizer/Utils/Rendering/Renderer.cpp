#include "Renderer.h"
#include <functional>
#include <sstream>

namespace mvlizer::rendering {

	// Shaders
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"in vec2 position;\n"
		"in vec3 i_color;\n"
		"out vec3 _color;\n"
		"void main()\n"
		"{\n"
		"_color = i_color;"
		"gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
		"}\0";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"in vec3 _color;"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(_color, 1.0f);\n"
		"}\n\0";

	std::shared_ptr<spikeylog::ILogger> Renderer::m_logger = nullptr;
	std::unordered_map<uint16_t, Renderer::keyCallback> Renderer::keycallbacks = std::unordered_map<uint16_t, keyCallback>();
	bool Renderer::_isGLFWInit = false;

	Renderer::Renderer(const std::shared_ptr<spikeylog::ILogger> &logger, data::Database &database)
		: data(database)
	{

		m_logger = logger;

		if (!_isGLFWInit) {
			m_logger->info("Initializing GLFW...");
			if (!glfwInit())
				throw std::runtime_error("GLFW Failed to init");
			else {
                _isGLFWInit = true;
				m_logger->info("Successfully initialized GLFW");

				// setting error callback
				m_logger->trace("Registering GLFW error callback");
				glfwSetErrorCallback(glfwErrorCallback);

				registerKeyCallback({ GLFW_KEY_ESCAPE, GLFW_PRESS }, [](KeyInputInfo _, GLFWwindow* win, Renderer* obj) {
					glfwSetWindowShouldClose(win, GL_TRUE);
					});

				registerKeyCallback({ GLFW_KEY_SPACE, GLFW_PRESS }, [](KeyInputInfo _, GLFWwindow* win, Renderer* obj) {
					glfwMakeContextCurrent(win);
					GLint mode[2];
					glGetIntegerv(GL_POLYGON_MODE, mode);
					glPolygonMode(GL_FRONT_AND_BACK, mode[1] == GL_FILL ? GL_LINE : GL_FILL);
					});

                registerKeyCallback({GLFW_KEY_F11, GLFW_PRESS}, [](KeyInputInfo _, GLFWwindow* win, Renderer* obj) {

                    // TODO: fix this mess
                    obj->data.isFullScreen = !obj->data.isFullScreen;

                    auto ptr = glfwGetPrimaryMonitor();
                    auto mode = glfwGetVideoMode(ptr);



                    int xpos, ypos, width, height;
                    glfwGetMonitorWorkarea(ptr, &xpos, &ypos, &width, &height);

                    if (obj->data.isFullScreen) {
                        glfwSetWindowMonitor(win, nullptr, 0, 0, obj->data.width, obj->data.height, 0);
                    } else {
                        glfwSetWindowMonitor(win, glfwGetPrimaryMonitor(), xpos, ypos, width, height,
                                             mode->refreshRate);
                    }
                });
			}
		}
		else {
			m_logger->warn("Cannot initialize GLFW, it is already initialized.");
		}

	}

	Renderer::~Renderer() {
		destroyWindow();
		if (_isGLFWInit) {
			m_logger->info("Terminating GLFW");
			glfwTerminate();
            _isGLFWInit = false;
		}
	}

	void Renderer::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyInputInfo info{ (uint16_t)key, (uint16_t)action };

		if (action == GLFW_PRESS) {
			// m_logger->trace((std::ostringstream() << "Key pressed: " << info.asStruct.key).str_());
		}
		auto callback = keycallbacks[info.asShort];

        Renderer* ptr = (Renderer*)glfwGetWindowUserPointer(window);

		if (callback) {
			callback(info, window, ptr);
		}
	}

	void Renderer::glfwWindowResizeCallback(GLFWwindow* window, int width, int height)
	{
        Renderer* data = (Renderer*)glfwGetWindowUserPointer(window);
        data->data.width = width;
        data->data.height = height;
		glfwMakeContextCurrent(window);
		glViewport(0, 0, width, height);
	}

	void Renderer::createWindow()
	{
		m_logger->trace("Creating window...");
		if (window == nullptr) {

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			int x, y, w, h;

			glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);


			window = glfwCreateWindow(800, 600, "window Name", nullptr, nullptr);
			if (!window) {
				throw std::runtime_error("Could not create window!");
			}
			else {
				m_logger->trace("window successfully created");
				glfwMakeContextCurrent(window);

				m_logger->trace("Initializing GLEW...");
				glewExperimental = GL_TRUE;
				GLenum err = glewInit();
				if (err != GLEW_OK) {
					std::ostringstream s;
					s << "Error initializing GLEW: " << (char*)glewGetErrorString(err);
					throw std::runtime_error(s.str().c_str());
				}

				
				std::ostringstream s;
				s << "GLEW version " << (char*)glewGetString(GLEW_VERSION) << " successfully initialized";
				m_logger->trace(s.str());

				m_logger->trace("Registering GLFW key callback");
				glfwSetKeyCallback(window, glfwKeyCallback);
				glfwSetWindowSizeCallback(window, glfwWindowResizeCallback);

				int width, height;
				glfwGetFramebufferSize(window, &width, &height);
				glViewport(0, 0, width, height);

                glfwSetWindowUserPointer(window, this);
			}
		}
		else {
			m_logger->warn("Cannot create window, one already exists");
		}

	}

	Renderer::keyCallback Renderer::registerKeyCallback(KeyInputInfo keyInfo, keyCallback callback) {
		keyCallback prev = keycallbacks[keyInfo.asShort];
		keycallbacks[keyInfo.asShort] = callback;
		return prev;
	}


	void Renderer::destroyWindow() {
		if (window != nullptr) {
			m_logger->trace("Destroying window");
			glfwDestroyWindow(window);
			window = nullptr;
		}
	}

	void Renderer::start()
	{
		m_logger->trace("setting swap interval to 1");
		glfwMakeContextCurrent(window);
		//glfwSwapInterval(1);

		// Build and compile our shader program
   // Vertex shader
		m_logger->trace("Compiling vertex shader...");
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		// Check for compile time errors
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::ostringstream s;
			s << "GL Vertex Shader Error: " << infoLog;
			m_logger->error(s.str());
		}
		else {
			m_logger->trace("Vertex shader successfully compiled");
		}
		// Fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);
		// Check for compile time errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::ostringstream s;
			s << "GL Fragment Shader Error: " << infoLog;
			m_logger->error(s.str());
		}
		// Link shaders
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// Check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::ostringstream s;
			s << "GL Shader Link Error: " << infoLog;
			m_logger->error(s.str());
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		// Set up vertex data (and buffer(s)) and attribute pointers
		// We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
		GLfloat* vertices = nullptr;
		unsigned int vertices_length = 0;
		GLuint* elements = nullptr;
		unsigned int elements_length = 0;

		GLuint VBO, VEO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VEO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_DYNAMIC_DRAW);

		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

		GLint colorAttrib = glGetAttribLocation(shaderProgram, "i_color");
		glEnableVertexAttribArray(colorAttrib);
		glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex::pos)));

		//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

        int l, l2;

        Vertex* v;
        GLint* e;

		// Game loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			updateRenderObjects();


			// Render
			// Clear the colorbuffer
			glClearColor(0.0, 0.0, 0.0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw our first triangle
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);


            compileArrays(v, e, l, l2);

            glBufferData(GL_ARRAY_BUFFER, l * sizeof(Vertex), v, GL_DYNAMIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, l2 * sizeof(GLint), e, GL_DYNAMIC_DRAW);

            delete v;
            delete e;

            glDrawElements(GL_LINE_STRIP, l2, GL_UNSIGNED_INT, nullptr);


            glBindVertexArray(0);

			// Swap the screen buffers
			glfwSwapBuffers(window);


		}
		data.should_close = true;
		// Properly de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}


	void Renderer::glfwErrorCallback(int error, const char* description) {
		std::ostringstream stream;
		stream << "GLFW Error " << error << ": \n\t" << description;
		m_logger->error(stream.str());
	}

	void Renderer::updateRenderObjects()
	{
		for (IRenderObject* obj : data.renderObjects) {
			obj->render();
		}
	}

	Vertex* Renderer::compVertexArray(int& length)
	{
		unsigned int l = 0;
		for (IRenderObject* i : data.renderObjects) {
			l += i->getVertexLength();
		}
		auto* result = new Vertex[l];
		unsigned int offset = 0;
		for (IRenderObject* i : data.renderObjects) {
			Vertex* v = i->getVertexArray();
			unsigned int size = i->getVertexLength();
			std::copy(v, v + size, result + offset);
			offset += size;
		}
		length = l;
		return result;
	}

	GLint* Renderer::compElemArray(int& length)
	{
		unsigned int l = 0;
		for (IRenderObject* i : data.renderObjects) {
			l += i->getElementLength();
		}
		auto* result = new GLint[l];
		unsigned int offset = 0;
		unsigned int e_offset = 0;
		for (IRenderObject* i : data.renderObjects) {
			GLint* v = i->getElementArray();
			unsigned int size = i->getElementLength();
			std::copy(v, v + size, result + offset);
			for (unsigned int index = offset; index < offset + size; ++index) {
				result[index] += e_offset;
			}
			offset += size;
			e_offset += i->getVertexLength();
		}
		length = l;
		return result;
	}

    void Renderer::compileArrays(Vertex*& vertices, GLint*& elements, int& vert_length, int& elem_length) {
        auto vert_result = new std::vector<Vertex>;
        auto elem_result = new std::vector<GLint>;



        for(auto* obj : data.renderObjects) {
            std::shared_lock<std::shared_mutex> lock(obj->access_mutex);
            int size = obj->getVertexLength();
            auto ptr = obj->getVertexArray();
            vert_result->resize(vert_result->size() + size);
            std::copy(ptr, ptr + size, vert_result->end() - size);

            int e_offset = vert_result->size() - size;



            auto ptr_2 = obj->getElementArray();
            unsigned int elem_size = obj->getElementLength();

            elem_result->resize(elem_result->size() + elem_size);
            std::copy(ptr_2, ptr_2 + elem_size, elem_result->end() - elem_size);
            for (auto iter = elem_result->end() - elem_size; iter != elem_result->end(); iter++) {
                *iter += e_offset;
            }

        }

        vertices = &vert_result->at(0);
        elements = &elem_result->at(0);
        vert_length = vert_result->size();
        elem_length = elem_result->size();
    }
}

