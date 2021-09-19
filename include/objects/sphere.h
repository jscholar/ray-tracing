#pragma once

#include "physics/vec3.h"
#include "physics/ray.h"
#include "objects/hittable.h"
#include "objects/material.h"

using namespace std;

class sphere : public hittable
{
public:
	shared_ptr<material> p_material;
	point3 center;
	color surfaceColor;
	double radius;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="center"></param>
	/// <param name="radius"></param>
	/// <param name="surfaceColor"></param>
	/// <returns></returns>
	sphere(
		const point3& center,
		double radius,
		const color& surfaceColor,
		const shared_ptr<material> p_material
	);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="ray"></param>
	/// <param name="t_min"></param>
	/// <param name="t_max"></param>
	/// <returns>The t value of the ray for the point of contact with the sphere.
	/// If the sphere does not block, DBL_MAX is returned</returns>
	double blocks(const ray& ray, double t_min, double t_max) const;

	vec3 outward_normal_at(const point3& point) const;

	color get_color_at(const point3& point) const;
};

