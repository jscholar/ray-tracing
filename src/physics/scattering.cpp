#include "physics/scattering.h"

#include "physics/vec3.h"
#include "physics/math_utils.h"

vec3 scattering::pseudo_lambertian_diffusion() {
    double x = (math_utils::random_double() * 2) - 1;
    double y = (math_utils::random_double() * 2) - 1;
    double z = (math_utils::random_double() * 2) - 1;

    vec3 random_vector = vec3(x, y, z);

    // calculate the distance from random vector to source vector
    // if <= 1, return it. 
    if (random_vector.length() <= 1) {
        return unit_vector(random_vector);
    }
    else {
        // if not, run again
        return pseudo_lambertian_diffusion();
    }
}

vec3 scattering::lambertian_diffusion() {
    double x = (math_utils::random_double() * 2) - 1;
    double y = (math_utils::random_double() * 2) - 1;
    double z = (math_utils::random_double() * 2) - 1;

    vec3 random_vector = vec3(x, y, z);

    // calculate the distance from random vector to source vector
    // if <= 1, return it. 
    if (random_vector.length() <= 1) {
        return unit_vector(random_vector);
    }
    else {
        // if not, run again
        return lambertian_diffusion();
    }
}


vec3 scattering::standard_diffusion(vec3 normal) {
    vec3 random_vector = pseudo_lambertian_diffusion();

    if (dot(random_vector, normal) > 0) {
        return random_vector;
    }
    else {
        return -random_vector;
    }
}