#include "BaseRenderObject.h"

namespace mvlizer {
	void BaseRenderObject::update()
	{
		std::unique_lock<std::shared_timed_mutex> write_lock(mut);
		onUpdate();
	}

	void BaseRenderObject::render()
	{
		std::shared_lock<std::shared_timed_mutex> read_lock(mut);
		onRender();
	}

	Vertex* BaseRenderObject::getVertexArray() {
		return &vertices[0];
	}

	GLint* BaseRenderObject::getElementArray() {
		return &elements[0];
	}

}