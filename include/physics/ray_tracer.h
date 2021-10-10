#pragma once

#include "physics/vec3.h"

class ray;
class hittable;
class material;

namespace ray_tracer {
	/**
	 * @brief The meat and potatoes babyyyy LET'S GOO!!!
	 * @param r 
	 * @param hittable_entity 
	 * @param bounce 
	*/
	color ray_color(const ray& r, const hittable& hittable_entity, int bounce);


	vec3 ray_scatter(vec3& incoming_direction, const material& material_hit, vec3& surface_normal);


	/**
	 * @brief Skybox color for a given ray
	*/
	color ray_skybox(const ray& r);
}
