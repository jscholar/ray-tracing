#include "objects/hit_list.h"

#include <optional>
#include "physics/vec3.h"
#include "objects/material.h"
#include "objects/hittable.h"
#include "objects/sphere.h"

hit_list::hit_list() {};
hit_list::hit_list(vector<shared_ptr<hittable>> input) : hittables{ input } {}

shared_ptr<material> mat_stone = make_shared<stone>(stone());

bool hit_list::find_hit(const ray& ray, const double t_min, const double t_max, hit_record& hrec) const {
    std::optional<hit_record> closest_hrec;

    // iterate over hittables
    for (const auto& hittable : hittables) {
        std::optional<hit_record> possible_hrec = hittable->find_hit(ray, t_min, t_max);

        if (!possible_hrec.has_value()) {
            continue;
        }

        if (!closest_hrec || possible_hrec->t < closest_hrec->t) {
            closest_hrec = possible_hrec;
        }
    }

    hrec = closest_hrec.value_or(hrec);
    return closest_hrec.has_value();
}