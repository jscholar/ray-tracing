#include "objects/hit_list.h"

#include "physics/vec3.h"
#include "objects/hittable.h"
#include "objects/material.h"

#include <vector>
#include <optional>
#include <memory>

hit_list::hit_list() {};
hit_list::hit_list(std::vector<std::shared_ptr<hittable>> input) : hittables{ input } {}

std::shared_ptr<material> mat_stone = std::make_shared<stone>(stone());

std::optional<hit_record> hit_list::find_hit(const ray& ray, const double t_min, const double t_max) const {
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

    return closest_hrec;
}