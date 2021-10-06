#pragma once

#include <optional>
#include "physics/vec3.h"
#include "physics/ray.h"
#include "objects/hittable.h"
#include "objects/material.h"

using namespace std;

class sphere : public hittable_object
{
public:
	shared_ptr<material> p_material;
	point3 center;
	color surfaceColor;
	double radius;

	sphere(
		const point3& center,
		double radius,
		const color& surfaceColor,
		const shared_ptr<material> p_material
	);

	std::optional<hit_record> find_hit(const ray& ray, double t_min, double t_max) const;

	vec3 outward_normal_at(const point3& point) const;

	color get_color_at(const point3& point) const;
};
