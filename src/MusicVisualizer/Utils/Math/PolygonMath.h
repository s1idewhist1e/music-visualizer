#pragma once
#ifndef POLYGONMATH_H
#define POLYGONMATH_H

#include <vector>
#include "Utils/Rendering/Objects/Vertex.h"

namespace mvlizer::math {
	using mvlizer::rendering::Vertex;
	class PolygonMath {

	public:
		static const double pi;
		static std::vector<int> triangulate2DPolygon(std::vector<Vertex> vertices);
		static bool isConvex(Vertex prev, Vertex curr, Vertex next);
		static double angleCCW(std::pair<double, double> one, std::pair<double, double> two);
		static bool pointIsInTriangle(Vertex a, Vertex b, Vertex c, Vertex t);
	};
}

#endif