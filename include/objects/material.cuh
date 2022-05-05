#pragma once

#include "physics/vec3.cuh"

class material {
public:
    virtual vec3 get_bounce_direction(vec3 incoming, vec3 normal) const = 0;
    virtual color get_reflectiveness() const = 0;
};

class fluorescent_white : public material {
    vec3 get_bounce_direction(vec3 incoming, vec3 normal) const;
    color get_reflectiveness() const;
};

class stone : public material {
    vec3 get_bounce_direction(vec3 incoming, vec3 normal) const;
    color get_reflectiveness() const;
};

class grass : public material {
    vec3 get_bounce_direction(vec3 incoming, vec3 normal) const;
    color get_reflectiveness() const;
};

class ocean : public material {
    vec3 get_bounce_direction(vec3 incoming, vec3 normal) const;
    color get_reflectiveness() const;
};

class metal : public material {
    vec3 get_bounce_direction(vec3 incoming, vec3 normal) const;
    color get_reflectiveness() const;
};

class gold : public material {
    vec3 get_bounce_direction(vec3 incoming, vec3 normal) const;
    color get_reflectiveness() const;
};
