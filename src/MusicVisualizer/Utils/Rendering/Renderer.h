#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <list>
#include <GLFW/glfw3.h>
#include <memory>
#include <portaudio.h>
#include <spikeylog.h>
#include <unordered_map>
#include "Objects/IRenderObject.h"
#include "Objects/Vertex.h"
#include "Utils/Data/Database.h"

/// \brief Classes surrounding rendering objects
namespace mvlizer::rendering {
	union KeyInputInfo
	{
		struct {
			uint16_t key : 9;
			uint16_t action : 7;
		} asStruct;

		uint16_t asShort;


	};
	

	typedef void(*keyCallback)(KeyInputInfo, GLFWwindow*);

	class Renderer{
	public:
		static keyCallback registerKeyCallback(KeyInputInfo keyInfo, keyCallback callback);
		virtual void createWindow();
		void destroyWindow();
		void start();
		Renderer(const std::shared_ptr<spikeylog::ILogger> &logger, data::Database &win);
		virtual ~Renderer();
	protected:
		static std::unordered_map<uint16_t, keyCallback> keycallbacks;
		static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void glfwWindowResizeCallback(GLFWwindow* window, int width, int height);
		static std::shared_ptr<spikeylog::ILogger> m_logger;
		GLFWwindow* window = nullptr;
		data::Database& data;
		static void glfwErrorCallback(int error, const char* description);
		double frametime;
		void updateRenderObjects();
		Vertex* compVertexArray(int &length);
		GLint* compElemArray(int& length);

	protected:
		static bool _isGLFWInit;
	};


}

#endif