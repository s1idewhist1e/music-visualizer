#pragma once
#ifndef FOURIER_TRANSFORMS_H
#define FOURIER_TRANSFORMS_H

#include <vector>
#include <cmath>
#include <iterator>

namespace mvlizer {
    template<typename T>
	class FourierTransforms {
	public:
		static std::vector<std::pair<double, double>> discreteFourierTransform(T begin, T end, int stride);
        static std::vector<std::pair<double, double>> fastFourierTransform(T begin, T end, unsigned char bl_exp);
	private:
		FourierTransforms() {};
	};



}

#endif