#pragma once
#ifndef BASERENDEROBJECT_H
#define BASERENDEROBJECT_H

#include "IRenderObject.h"
#include <shared_mutex>
#include <mutex>
#include <vector>

namespace mvlizer::rendering {
	class BaseRenderObject : public IRenderObject {
	public:
		// locks render thread for update
		virtual void onUpdate() = 0;
		// locks shared mutex, should not write any data
		virtual void onRender() = 0;

		Vertex* getVertexArray() override;
		GLint* getElementArray() override;

		unsigned int getVertexLength() override { return vertices.size(); }
		unsigned int getElementLength() override { return elements.size(); }

		void tick() override;
		void render() override;

        ~BaseRenderObject() override = default;

	private:
		std::shared_mutex mut;
	protected:
		std::vector<Vertex> vertices;
		std::vector<GLint> elements;
	};
}

#endif
