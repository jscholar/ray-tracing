#pragma once

#include "physics/ray.h"
#include "physics/vec3.h"
#include "objects/material.h"

class hittable {
public:
    std::shared_ptr<material> p_material;
    point3 center;

    virtual double blocks(const ray& ray, double t_min, double t_max) const = 0;
    virtual vec3 outward_normal_at(const point3& point) const = 0;
    virtual color get_color_at(const point3& point) const = 0;
};

struct hit_record {
    double t = DBL_MAX;
    vec3 normal;
    bool front_hit;
    std::shared_ptr<hittable> object_hit;
};
