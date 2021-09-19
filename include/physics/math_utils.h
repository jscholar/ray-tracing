#pragma once

#include "physics/vec3.h"

namespace math_utils {
	double degrees_to_radians(double degrees);

	/// <summary>
	/// Generates a random double  [0.0 inclusive to 1.0 exclusive]
	/// </summary>
	double random_double();

	vec3 random_vector_unit_sphere(vec3 normal);
}
