#pragma once

#include "physics/vec3.h"

namespace scattering
{
	vec3 pseudo_lambertian_diffusion();

	vec3 lambertian_diffusion();

	vec3 standard_diffusion(vec3 normal);
};
