#pragma once
#ifndef IRENDEROBJECT_H
#define IRENDEROBJECT_H

#include <spikeylog.h>
#include "Vertex.h"

namespace mvlizer {
	class IRenderObject {
	public: 
		virtual Vertex* getVertexArray() = 0;
		virtual GLint* getElementArray() = 0;
		virtual unsigned int getVertexLength() = 0;
		virtual unsigned int getElementLength() = 0;
		virtual void render() = 0;
		virtual void update() = 0;
		bool isUpdated = true;
		
	};
}

#endif
