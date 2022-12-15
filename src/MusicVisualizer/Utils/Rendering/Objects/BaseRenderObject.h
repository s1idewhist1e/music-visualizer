#pragma once
#ifndef BASERENDEROBJECT_H
#define BASERENDEROBJECT_H

#include "IRenderObject.h"
#include <shared_mutex>
#include <mutex>
#include <vector>

namespace mvlizer {
	class BaseRenderObject : public IRenderObject {
	public:
		// locks render thread for update
		virtual void onUpdate() = 0;
		// locks shared mutex, should not write any data
		virtual void onRender() = 0;

		virtual Vertex* getVertexArray();
		virtual GLint* getElementArray();

		unsigned int getVertexLength() { return vertices.size(); }
		unsigned int getElementLength() { return elements.size(); }

		void tick();
		void render();

	private:
		std::shared_timed_mutex mut;
	protected:
		std::vector<Vertex> vertices;
		std::vector<GLint> elements;
	};
}

#endif
