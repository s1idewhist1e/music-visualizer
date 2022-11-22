//#include "TestRenderObject.h"
//#include <chrono>
//
//namespace mvlizer {
//	TestRenderObject::TestRenderObject()
//		: vert{ {-0.5f, 0.5f, 1.0f, 1.0f, 1.0f }, {0.5f, 0.5f, 1.0f, 1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f, 1.0f}, {-0.5f, -0.5f, 1.0f, 1.0f, 1.0f} },
//		elem{ 0, 1, 2, 3, 2, 0 }
//	{
//		for (int i = 0; i < 4; ++i) {
//			old[i] = vert[i];
//			_new[i].pos.x = (1 - (2 * (rand() / (float)RAND_MAX)));
//			_new[i].pos.y = (1 - (2 * (rand() / (float)RAND_MAX)));
//		}
//	}
//
//
//	void TestRenderObject::onRender() {
//
//	}
//	void TestRenderObject::onUpdate()
//	{
//		for (int i = 0; i < 4; ++i) {
//			//v.pos.x += (0.5 - (rand() / (float)RAND_MAX)) / 100;
//			//v.pos.y += (0.5 - (rand() / (float)RAND_MAX)) / 100;
//			if (time >= 1) {
//				for (int j = 0; j < 4; ++j) {
//					old[j].pos = vert[j].pos;
//					_new[j].pos.x = (1 - (2 * (rand() / (float)RAND_MAX)));
//					_new[j].pos.y = (1 - (2 * (rand() / (float)RAND_MAX)));
//				}
//				time = 0;
//			}
//
//			double _t = time * time * (3 - 2 * time);
//			vert[i].pos.x = ((_new[i].pos.x - old[i].pos.x) * _t) + old[i].pos.x;
//			vert[i].pos.y = ((_new[i].pos.y - old[i].pos.y) * _t) + old[i].pos.y;
//
//
//		}
//		time += 0.01;
//	}
//	TestRenderObject::~TestRenderObject()
//	{
//	}
//}