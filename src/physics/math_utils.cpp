#include "physics/math_utils.h"

#include <limits>
#include <memory>
#include <random>

#include "physics/scattering.h"
#include "physics/vec3.h"

double math_utils::random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

vec3 math_utils::random_vector_unit_sphere(vec3 normal) {
    return scattering::standard_diffusion(normal);
}
