#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC

#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Objects/IRenderObject.h"
#include "Objects/Vertex.h"
#include <spikeylog.h>
#include <unordered_map>
#include <portaudio.h>
#include "Utils/Data/Database.h"

namespace mvlizer {
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
		void createWindow();
		void destroyWindow();
		void start();
		Renderer(std::shared_ptr<spikeylog::ILogger> logger, Database& database);
		~Renderer();
	private:
		static std::unordered_map<uint16_t, keyCallback> keycallbacks;
		static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void glfwWindowResizeCallback(GLFWwindow* window, int width, int height);
		GLFWwindow* window = nullptr;
		static std::shared_ptr<spikeylog::ILogger> m_logger;
		Database& data;
		static void glfwErrorCallback(int error, const char* description);
		double frametime;
		void updateRenderObjects();
		Vertex* compVertexArray(int &length);
		GLint* compElemArray(int& length);

	protected:
		static bool _isGLFWinit;
	};


}

#endif