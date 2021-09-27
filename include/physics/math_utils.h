#pragma once

#include "physics/vec3.h"

namespace math_utils {
	/**
	 * @brief Generates a random double  [0.0 inclusive to 1.0 exclusive]
	*/
	double random_double();

	/**
	 * @brief Generates a random 3d vector
	 * @param magnitude: Magnitude of the generated vector.
	*/
	vec3 random_vector(double magnitude = 1.0);

	/**
	 * @brief Generates a random 3d vector
	 * @param min_magnitude: Minimum magnitude of generated vector [inclusive]
	 * @param max_magnitude: Maximum magnitude of generated vector [exclusive]
	*/
	vec3 random_vector(double min_magnitude, double max_magnitude);
}
