#pragma once
#ifndef FOURIER_TRANSFORMS_H
#define FOURIER_TRANSFORMS_H

#include <vector>
#include <cmath>

namespace mvlizer {
	static class FourierTransforms {
	public:
		static std::vector<std::pair<double, double>> discreteFourierTransform(std::vector<double> dataset, int stride);
	private:
		FourierTransforms() {};
	};

}

#endif