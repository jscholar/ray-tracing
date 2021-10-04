#pragma once

#include <optional>
#include "physics/ray.h"
#include "physics/vec3.h"
#include "objects/material.h"

struct hit_record;

class hittable : public std::enable_shared_from_this<hittable> {
public:
    std::shared_ptr<material> p_material;
    point3 center;

    virtual std::optional<hit_record> find_hit(const ray& ray, double t_min, double t_max) const = 0;
    virtual vec3 outward_normal_at(const point3& point) const = 0;
    virtual color get_color_at(const point3& point) const = 0;
};

struct hit_record {
	double t;
	vec3 normal;
	std::shared_ptr<const hittable> object_hit;
};
