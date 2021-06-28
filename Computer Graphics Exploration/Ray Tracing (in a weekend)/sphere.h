#pragma once

#include <iostream>
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

using namespace std;

class sphere : public hittable
{
	public: 
		point3 center;
		color surfaceColor;
		double radius;

		sphere() {};
		/// <summary>
		/// 
		/// </summary>
		/// <param name="center"></param>
		/// <param name="radius"></param>
		/// <param name="surfaceColor"></param>
		/// <returns></returns>
		sphere(const point3& center, double radius, const color& surfaceColor) 
			: center( center ), radius(radius), surfaceColor(surfaceColor) {};

		/// <summary>
		/// 
		/// </summary>
		/// <param name="ray"></param>
		/// <param name="t_min"></param>
		/// <param name="t_max"></param>
		/// <returns>The t value of the ray for the point of contact with the sphere.
		/// If the sphere does not block, DBL_MAX is returned</returns>
		double blocks(const ray& ray, double t_min, double t_max) const {
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

		vec3 outward_normal_at(const point3& point) const {
			return unit_vector(point - center);
		}
};

