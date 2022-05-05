#include "objects/material.h"

#include "physics/vec3.h"
#include "physics/scattering.h"
#include "physics/math_utils.h"

// fluorescent
vec3 fluorescent_white::get_bounce_direction(vec3 incoming, vec3 normal) const {
	return scattering::lambertian_diffusion(incoming, normal);
}
color fluorescent_white::get_reflectiveness() const {
	double magnitude = 100.0;
	color tint = color(1, 1, 1);
	return magnitude * tint;
}

// stone
vec3 stone::get_bounce_direction(vec3 incoming, vec3 normal) const {
	return scattering::standard_diffusion(incoming, normal);
}
color stone::get_reflectiveness() const {
	double magnitude = 0.65;
	color tint = color(1, 1, 1);
	return magnitude * tint;
}

// grass
vec3 grass::get_bounce_direction(vec3 incoming, vec3 normal) const {
	return scattering::standard_diffusion(incoming, normal);
}
color grass::get_reflectiveness() const {
	double magnitude = 0.45;
	color tint = color(0.3, 1, 0.15);
	return magnitude * tint;
}

// ocean
vec3 ocean::get_bounce_direction(vec3 incoming, vec3 normal) const {
	return scattering::fuzzy_reflection(incoming, normal, 0.5);
}
color ocean::get_reflectiveness() const {
	double magnitude = 0.3;
	color tint = color(0.5, 0.6, 1);
	return magnitude * tint;
}

// metal
vec3 metal::get_bounce_direction(vec3 incoming, vec3 normal) const {
	return scattering::true_reflection(incoming, normal);
}
color metal::get_reflectiveness() const {
	color tint = color(1, 1, 1);
	double magnitude = 0.9;
	return magnitude * tint;
}

// gold
vec3 gold::get_bounce_direction(vec3 incoming, vec3 normal) const {
	return scattering::fuzzy_reflection(incoming, normal, 0.2);
}
color gold::get_reflectiveness() const {
	color gold_tint = color(1, 215.0 / 255.0, 0);
	double magnitude = 0.65;
	return magnitude * gold_tint;
}
