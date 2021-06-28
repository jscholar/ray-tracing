#pragma once

#include "hittable.h"
#include "vec3.h"
#include "sphere.h"

class hit_list {
public:
    vector<hittable*> hittables = {};

    hit_list() {}
    hit_list(vector<hittable*> input) : hittables(input) {}

    bool find_hit(const ray& ray, const double t_min, const double t_max, hit_record& hrec) {
        hittable* closest_hittable = &sphere(ray.orig, 1.0, ray.orig);

        // iterate over hittables
        for (hittable* p_hittable : hittables) {
            double hit = (*p_hittable).blocks(ray, t_min, t_max);
            if (hit < hrec.t) {
                hrec.t = hit;
                closest_hittable = p_hittable;
            }
        }

        // If hit nothing, return false
        if (hrec.t == DBL_MAX) {
            return false;
        }

        // Find the normal vector
        hrec.normal = (*closest_hittable).outward_normal_at(ray.at(hrec.t));

        // If normal and ray are same direction, flip the normal
        hrec.front_hit = true;
        if (dot(hrec.normal, ray.dir) > 0) {
            hrec.normal *= -1;
            hrec.front_hit = false;
        }

        return true;
    }
};
