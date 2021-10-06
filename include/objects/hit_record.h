#pragma once

#include <memory>

#include "physics/vec3.h"

class hittable_object;

struct hit_record {
	double t;
	vec3 normal;
	std::shared_ptr<const hittable_object> object_hit;
};