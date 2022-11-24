#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <GLFW/glfw3.h>

namespace mvlizer {
	struct Vertex {
		struct {
			GLfloat x, y;
		} pos;
		struct {
			GLfloat r, g, b;
		} color;

	};
}
#endif