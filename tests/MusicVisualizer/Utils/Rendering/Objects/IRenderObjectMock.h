#pragma once
#ifndef IRENDEROBJECT_MOCK_H
#define IRENDEROBJECT_MOCK_H
#include "Utils/Rendering/Objects/IRenderObject.h"
#include <gmock/gmock.h>

namespace mvlizer {
	namespace tests {
		class MockIRenderObject : public mvlizer::IRenderObject {
		public:
			MockIRenderObject() = default;
			MOCK_METHOD(Vertex*, getVertexArray, (), (override));
			MOCK_METHOD(GLint*, getElementArray, (), (override));
			MOCK_METHOD(unsigned int, getVertexLength, (), (override));
			MOCK_METHOD(unsigned int, getElementLength, (), (override));
			MOCK_METHOD(void, render, (), (override));
			MOCK_METHOD(void, tick, (), (override));			
		};
	}
}
#endif