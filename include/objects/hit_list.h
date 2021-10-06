#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "physics/vec3.h"
#include "objects/hittable.h"
#include "objects/sphere.h"

class hit_list : public hittable {
public:
    vector<shared_ptr<hittable>> hittables{};

    hit_list();
    hit_list(vector<shared_ptr<hittable>> input);

    std::optional<hit_record> find_hit(const ray& ray, const double t_min, const double t_max) const;
};
