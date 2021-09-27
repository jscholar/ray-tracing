#include "objects/sphere.h"

#include "math.h"
#include "objects/hittable.h"
#include "objects/material.h"
#include "physics/math_utils.h"
#include "physics/vec3.h"
#include "physics/ray.h"
#include "physics/scattering.h"

sphere::sphere(const point3& center, double radius, const color& surfaceColor, const shared_ptr<material> p_material)
	: center{ center }, radius{ radius }, surfaceColor{ surfaceColor }, p_material{ p_material }{};

double sphere::blocks(const ray& ray, double t_min, double t_max) const {
	point3 A = ray.orig;
	vec3 b = ray.dir;
	point3 C = center;

	// t^2b.b
	double q_a = dot(b, b);

	// 2tb.(A−C)
	double q_b = 2 * dot(b, A - C);

	// (A−C).(A−C)−r^2
	double q_c = dot(A - C, A - C) - (radius * radius);

	// Check direction of the ray
	double discriminant = (q_b * q_b) - (4 * q_a * q_c);
	if (discriminant < 0) {
		return DBL_MAX;
	}

	double root = (-q_b - sqrt(discriminant)) / (2 * q_a);

	// Check range of the ray
	if (root > t_max || root < t_min) {
		root = (-q_b + sqrt(discriminant)) / (2 * q_a);
		if (root > t_max || root < t_min) {
			return DBL_MAX;
		}
	}

	return root;
}

vec3 sphere::outward_normal_at(const point3& point) const {
	return unit_vector(point - center);
}

color sphere::get_color_at(const point3& point) const {
	// something similar to outward_normal_at
	// calculate the regular normal
	vec3 normal = outward_normal_at(point);

	// calculate a random point nearby (s)
	// return the vector from point to s
	return scattering::standard_diffusion(normal);
}
