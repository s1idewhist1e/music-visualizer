#pragma once
#ifndef FOURIER_TRANSFORMS_H
#define FOURIER_TRANSFORMS_H

#include <vector>
#include <cmath>
#include <iterator>

namespace mvlizer {
    template<std::input_iterator T>
	class FourierTransforms {
	public:
		static std::vector<std::pair<double, double>> discreteFourierTransform(T begin, T end, int stride);
	private:
		FourierTransforms() {};
	};

}

#endif