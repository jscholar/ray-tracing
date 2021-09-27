#include "physics/scattering.h"

#include "physics/vec3.h"
#include "physics/math_utils.h"

vec3 scattering::pseudo_lambertian_diffusion() {
    return math_utils::random_vector(0.0, 1.0);
}

vec3 scattering::lambertian_diffusion() {
    return math_utils::random_vector();
}

vec3 scattering::standard_diffusion(vec3 normal) {
    vec3 random_vector = pseudo_lambertian_diffusion();

    if (dot(random_vector, normal) > 0) {
        return unit_vector(random_vector);
    }
    else {
        return -unit_vector(random_vector);
    }
}