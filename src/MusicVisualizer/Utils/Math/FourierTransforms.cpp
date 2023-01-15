#include <deque>
#include "FourierTransforms.h"

namespace mvlizer {

    template<std::input_iterator T>
	std::vector<std::pair<double, double>> FourierTransforms<T>::discreteFourierTransform(T begin, T end, int stride)
	{
        std::vector<double> dataset(begin, end);
		const double pi = 3.14159265358979323846;
		std::vector<std::pair<double, double>> values;
		for (int i = 1; i < dataset.size(); i+=stride) {
			double sin = 0.;
			double cos = 0.;
			for (int j = 0; j < dataset.size(); ++j) {
				sin += (dataset[j] * std::sin(i * 2 * pi * ((double)j / pi)));
				cos += (dataset[j] * std::cos(i * 2 * pi * ((double)j / pi)));
			}
			values.push_back(std::pair<double, double>(sin / dataset.size(), cos / dataset.size()));
		}
		return values;
	}

    template class FourierTransforms<std::deque<float>::iterator>;
}