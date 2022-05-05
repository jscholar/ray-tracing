#include "physics/scattering.h"

#include "physics/vec3.h"
#include "physics/math_utils.h"

vec3 scattering::pseudo_lambertian_diffusion(vec3 incoming, vec3 normal) {
    return normal + math_utils::random_vector(0.0, 1.0);
}

vec3 scattering::lambertian_diffusion(vec3 incoming, vec3 normal) {
    vec3 scattered = normal + math_utils::random_vector(1.0);
    if (scattered.length() == 0) {
        return scattering::lambertian_diffusion(incoming, normal);
    }
    return scattered;
}

vec3 scattering::true_reflection(vec3 incoming, vec3 normal) {
    double s = dot(incoming, normal);
    vec3 normal_component = s * normal;
    vec3 outgoing = incoming - (2 * normal_component);
    return outgoing;
}

vec3 scattering::standard_diffusion(vec3 incoming, vec3 normal) {
    vec3 random_vector = math_utils::random_vector(0.0001, 1.0);

    if (dot(random_vector, normal) > 0) {
        return unit_vector(random_vector);
    }
    else {
        return -unit_vector(random_vector);
    }
}

vec3 scattering::fuzzy_reflection(vec3 incoming, vec3 normal, double fuzziness) {
    vec3 reflected = scattering::true_reflection(incoming, normal);
    vec3 offset = math_utils::random_vector(fuzziness);

    vec3 fuzzy = reflected + offset;

    if (dot(fuzzy, normal) > 0) {
        return fuzzy;
    }
    else {
        return scattering::fuzzy_reflection(incoming, normal, fuzziness);
    }
}
