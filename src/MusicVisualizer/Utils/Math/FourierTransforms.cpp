#include <deque>
#include "FourierTransforms.h"

namespace mvlizer {

    template<typename T>
	std::vector<std::pair<double, double>> FourierTransforms<T>::discreteFourierTransform(T begin, T end, int stride)
	{
        std::vector<double> dataset(begin, end);
		static const double pi = 3.14159265358979323846;
		std::vector<std::pair<double, double>> values;
		for (int i = 1; i < dataset.size() / 2; i+=stride) {
			double sin = 0;
			double cos = 0;
			for (int j = 0; j < dataset.size(); ++j) {
				sin += (dataset[j] * std::sin(i * 2 * pi * ((double)j / pi)));
				cos += (dataset[j] * std::cos(i * 2 * pi * ((double)j / pi)));
			}
			values.emplace_back(std::pair<double, double>(sin * 2 * pi / dataset.size(), cos * 2 * pi / dataset.size()));
		}
		return values;
	}

    template<typename T>
    std::vector<std::pair<double, double>>
    FourierTransforms<T>::fastFourierTransform(T begin, T end, unsigned char bl_exp) {
        unsigned long long blocklength = 1 << bl_exp;
        return std::vector<std::pair<double, double>>();
    }

    template class FourierTransforms<std::deque<float>::iterator>;
}