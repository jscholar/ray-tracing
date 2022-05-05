#pragma once

#include "objects/hittable_object.cuh"
#include "physics/vec3.cuh"

#include <optional>

struct hit_record;
class material;

class sphere : public hittable_object
{
public:
	std::shared_ptr<material> p_material;
	point3 center;
	color surfaceColor;
	double radius;

	sphere(
		const point3& center,
		double radius,
		const color& surfaceColor,
		const std::shared_ptr<material> p_material
	);

	std::optional<hit_record> find_hit(const ray& ray, double t_min, double t_max) const;

	vec3 outward_normal_at(const point3& point) const;
};
