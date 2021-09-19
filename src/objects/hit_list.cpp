#include "objects/hit_list.h"

#include "physics/vec3.h"
#include "objects/material.h"
#include "objects/hittable.h"
#include "objects/sphere.h"

hit_list::hit_list() {};
hit_list::hit_list(vector<shared_ptr<hittable>> input) : hittables{ input } {}

shared_ptr<material> mat_stone = make_shared<stone>(stone());
bool hit_list::find_hit(const ray& ray, const double t_min, const double t_max, hit_record& hrec) const {
    shared_ptr<hittable> closest_hittable = make_shared<sphere>(sphere(ray.origin(), 1.0, ray.direction(), mat_stone));

    // iterate over hittables
    for (const auto& hittable : hittables) {
        double hit = hittable->blocks(ray, t_min, t_max);
        if (hit < hrec.t) {
            hrec.t = hit;
            closest_hittable = hittable;
        }
    }

    // If hit nothing, return false
    if (hrec.t == DBL_MAX) {
        return false;
    }

    // Find the normal vector and contact point
    hrec.object_hit = closest_hittable;
    // hrec.normal = (*closest_hittable).outward_normal_at(ray.at(hrec.t));
    vec3 normal = (*closest_hittable).outward_normal_at(ray.at(hrec.t));
    hrec.normal = normal;

    // If normal and ray are same direction, flip the normal
    hrec.front_hit = true;
    if (dot(normal, ray.dir) > 0) {
        normal *= -1;
        hrec.front_hit = false;
    }

    return true;
}