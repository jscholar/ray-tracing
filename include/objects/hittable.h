#pragma once

#include <optional>
#include <memory>

#include "physics/vec3.h"

struct hit_record;
class hittable_object;
class ray;

/**
 * @brief Representation of an entity hittable by a ray
*/
class hittable {
public:
    virtual std::optional<hit_record> find_hit(const ray& ray, double t_min, double t_max) const = 0;
};

struct hit_record {
	double t;
	vec3 normal;
	std::shared_ptr<const hittable_object> object_hit;
};