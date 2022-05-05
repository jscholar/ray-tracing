#include "physics/math_utils.cuh"

#include <limits>
#include <memory>
#include <random>

#include "physics/scattering.cuh"
#include "physics/vec3.cuh"

double math_utils::random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

vec3 math_utils::random_vector(double magnitude) {
	double x = (math_utils::random_double() * 2) - 1;
	double y = (math_utils::random_double() * 2) - 1;
	double z = (math_utils::random_double() * 2) - 1;

	vec3 new_random_vector = vec3(x, y, z);

	if (new_random_vector.length() <= 1) {
		return unit_vector(new_random_vector) * magnitude;
	}
	else {
		return math_utils::random_vector(magnitude);
	}
}

// TODO: Negative inputs
vec3 math_utils::random_vector(double min_magnitude, double max_magnitude) {
	if (min_magnitude > max_magnitude) {
		std::cout << "Received (min: " << min_magnitude << ")" << " and (max: " << max_magnitude << "), inferring the opposite";
		return random_vector(max_magnitude, min_magnitude);
	}

	// Generate a uniformly random magnitude.
	const double delta = std::pow(random_double(), 1 / 3) * max_magnitude - min_magnitude;
	const double magnitude =  std::abs(min_magnitude + delta);

	return random_vector(magnitude);
}
