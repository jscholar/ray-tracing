#pragma once

#include "physics/vec3.cuh"

class ray {
public:
    point3 orig;
    vec3 dir;

    ray();
    ray(const point3& origin, const vec3& direction);

    point3 origin() const;
    vec3 direction() const;
    point3 at(double t) const;
};