#include <list>
#include "PolygonMath.h"

namespace mvlizer::math {
	const double PolygonMath::pi = 3.14159265358979323846;

	std::vector<int> PolygonMath::triangulate2DPolygon(std::vector<Vertex> vertices) {
		std::vector<int> elements;
		int i = 0;
		std::list<std::pair<Vertex, int>> list;
		for (auto iter = vertices.begin(); iter != vertices.end(); ++iter) {
			list.push_back(std::pair(*iter, i));
			i++;
		}

		auto node = list.begin();
		while (list.size() > 2) {
			std::list<std::pair<Vertex, int>>::iterator prev;

			if (node == list.end()) {
				node = list.begin();
			}

			if (node == list.begin()) {
				prev = std::prev(list.end());
			}
			else {
				prev = std::prev(node);
			}

			std::list<std::pair<Vertex, int>>::iterator next = std::next(node);
			if (next == list.end()) {
				next = list.begin();
			}
			bool is_convex = isConvex(( * prev).first, ( * node).first, ( * next).first);
			bool is_ear = true;
			if (is_convex) {
				for (auto i = list.begin(); i != list.end(); ++i) {
					if (i != prev && i != node && i != next) {
						is_ear = !pointIsInTriangle(prev->first, node->first, next->first, i->first);
						if (!is_ear)
							break;
					}
				}
			}
			else {
				is_ear = false;
			}
			if (is_ear) {
				elements.push_back((* prev).second);
				elements.push_back((* node).second);
				elements.push_back((* next).second);
				//elements.push_back((*prev).second);

				node = list.erase(node); // erase returns the iterator to the element following the erased iterator
				continue;
			}
			
			++node;

		}
		return elements;
	}

	bool PolygonMath::isConvex(Vertex prev, Vertex curr, Vertex next) {
		std::pair<double, double> one(prev.pos.x - curr.pos.x, prev.pos.y - curr.pos.y);
		std::pair<double, double> two(next.pos.x - curr.pos.x, next.pos.y - curr.pos.y);
		double cross_3 = one.first * two.second - one.second * two.first;
		return cross_3 >= 0;
	}


	float sign(Vertex p1, Vertex p2, Vertex p3)
	{
		return (p1.pos.x - p3.pos.x) * (p2.pos.y - p3.pos.y) - (p2.pos.x - p3.pos.x) * (p1.pos.y - p3.pos.y);
	}

	bool PolygonMath::pointIsInTriangle(Vertex a, Vertex b, Vertex c, Vertex t) {

		float d1, d2, d3;
		bool has_neg, has_pos;

		d1 = sign(t, a, b);
		d2 = sign(t, b, c);
		d3 = sign(t, c, a);

		has_neg = (d1 <= 0) || (d2 <= 0) || (d3 <= 0);
		has_pos = (d1 >= 0) || (d2 >= 0) || (d3 >= 0);

		return !(has_neg && has_pos);



		//std::pair<double, double> one(a.pos.x - t.pos.x, a.pos.y - t.pos.y);
		//std::pair<double, double> two(b.pos.x - t.pos.x, b.pos.y - t.pos.y);
		//std::pair<double, double> three(c.pos.x - t.pos.x, c.pos.y - t.pos.y);

		//double dot11 = one.first * one.first + one.second * one.second;
		//double dot12 = one.first * two.first + one.second * two.second;
		//double dot13 = one.first * three.first + one.second * three.second;
		//double dot22 = two.first * two.first + two.second * two.second;
		//double dot23 = two.first * three.first + two.second * three.second;

		//double denom = dot11 * dot22 - dot12 * dot12;
		//if (abs(denom) < 1e-16) return true;
		//double invdenom = 1.0 / denom;
		//double u = (dot22 * dot13 - dot12 * dot23) * invdenom;
		//double v = (dot11 * dot23 - dot12 * dot13) * invdenom;
		//return (u >= 0 && v >= 0 && (u + v) < 1);
	};

}