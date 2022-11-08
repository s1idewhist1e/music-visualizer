#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include "IRenderObject.h"

namespace mvlizer {
	class Renderer {
	public:
		Renderer();
		void Render();
	private:
		std::list<IRenderObject> _renderObjects;
	};
}

#endif