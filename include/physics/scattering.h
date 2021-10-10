#pragma once

#include "physics/vec3.h"

namespace scattering
{
	/**
	 * @brief Scatters the ray to a random point within the unit sphere
	 *  offset by the unit from the point of incidence
	*/
	vec3 pseudo_lambertian_diffusion();

	/**
	 * @brief Scatters the ray to a random point on the surface if the unit sphere
	 *  offset by the unit from the point of incidence
	*/
	vec3 lambertian_diffusion();

	vec3 true_reflection(vec3 incoming, vec3 normal);

	vec3 standard_diffusion(vec3 normal);
};
