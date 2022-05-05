#include "objects/sphere.cuh"

#include "physics/vec3.cuh"
#include "physics/ray.cuh"
#include "physics/scattering.cuh"
#include "objects/material.cuh"
#include "objects/hittable.cuh"
#include "objects/hittable_object.cuh"

#include <optional>
#include <math.h>

sphere::sphere(const point3& center, double radius, const color& surface_color, const std::shared_ptr<material> p_material)
	: center{ center }, radius{ radius }, surfaceColor{ surface_color }, hittable_object{ p_material } {};

std::optional<hit_record> sphere::find_hit(const ray& ray, double t_min, double t_max) const {
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
		return std::nullopt;
	}

	double root = (-q_b - sqrt(discriminant)) / (2 * q_a);

	// Check range of the ray
	if (root > t_max || root < t_min) {
		root = (-q_b + sqrt(discriminant)) / (2 * q_a);
		if (root > t_max || root < t_min) {
			return std::nullopt;
		}
	}

	hit_record hrec;
	hrec.t = root;
	hrec.normal = outward_normal_at(ray.at(hrec.t));
	if (dot(ray.dir, hrec.normal) > 0) {
		hrec.normal *= -1;
	}
	hrec.object_hit = shared_from_this();

	return hrec;
}

vec3 sphere::outward_normal_at(const point3& point) const {
	return unit_vector(point - center);
}
