#include "BaseRenderObject.h"

namespace mvlizer::rendering {
	void BaseRenderObject::tick()
	{
		std::unique_lock<std::shared_mutex> write_lock(access_mutex);
		onUpdate();
	}

	void BaseRenderObject::render()
	{
		std::unique_lock<std::shared_mutex> read_lock(access_mutex);
		onRender();
	}

	Vertex* BaseRenderObject::getVertexArray() {
		return &vertices[0];
	}

	GLint* BaseRenderObject::getElementArray() {
		return &elements[0];
	}

}