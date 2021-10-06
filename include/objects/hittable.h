#pragma once

#include <optional>
#include "physics/ray.h"
#include "physics/vec3.h"
#include "objects/material.h"

struct hit_record;

/**
 * @brief Representation of an entity hittable by a ray
*/
class hittable {
public:
    virtual std::optional<hit_record> find_hit(const ray& ray, double t_min, double t_max) const = 0;
};

/**
 * @brief Representation of a single geometric hittable object (such as a sphere)
*/
class hittable_object : public std::enable_shared_from_this<hittable_object>, public hittable {
public:
	std::shared_ptr<material> p_material;

	virtual vec3 outward_normal_at(const point3& point) const = 0;
	virtual color get_color_at(const point3 & point) const = 0;
};

struct hit_record {
	double t;
	vec3 normal;
	std::shared_ptr<const hittable_object> object_hit;
};
