#include "objects/material.h"

#include "physics/vec3.h"
#include "physics/scattering.h"

// fluorescent
vec3 fluorescent::get_bounce_direction(vec3 normal) const {
	return scattering::lambertian_diffusion();
}
double fluorescent::get_reflectiveness() const {
	return 5.0;
}

// stone
vec3 stone::get_bounce_direction(vec3 normal) const {
	return scattering::standard_diffusion(normal);
}
double stone::get_reflectiveness() const {
	return 0.5;
}

// metal
vec3 metal::get_bounce_direction(vec3 normal) const {
	return scattering::standard_diffusion(normal);
}
double metal::get_reflectiveness() const {
	return 0.9;
}
