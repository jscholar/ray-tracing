#include "objects/hittable_object.cuh"

hittable_object::hittable_object(std::shared_ptr<material> p_material) : p_material{ p_material } {};
