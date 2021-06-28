#pragma once

#include "ray.h"
#include "sphere.h"
#include <cfloat>
#include <vector>

using namespace std;

struct hit_record {
    double t = DBL_MAX;
    vec3 normal;
    bool front_hit;
};
 
class hittable {
    public:
        virtual double blocks(const ray& ray, double t_min, double t_max) const = 0;
        virtual vec3 outward_normal_at(const point3& point) const = 0;
};
