#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "objects/hittable.cuh"

class ray;
struct hit_record;

class hit_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> hittables{};

    hit_list();
    hit_list(std::vector<std::shared_ptr<hittable>> input);

    std::optional<hit_record> find_hit(const ray& ray, const double t_min, const double t_max) const;
};
