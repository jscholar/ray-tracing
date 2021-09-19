#pragma once

#include "physics/vec3.h"

class material {
public:
    virtual vec3 get_bounce_direction(vec3 normal) const = 0;
    virtual double get_reflectiveness() const = 0;
};

class fluorescent : public material {
    vec3 get_bounce_direction(vec3 normal) const;
    double get_reflectiveness() const;
};

class stone : public material {
    vec3 get_bounce_direction(vec3 normal) const;
    double get_reflectiveness() const;
};

class metal : public material {
    vec3 get_bounce_direction(vec3 normal) const;
    double get_reflectiveness() const;
};
