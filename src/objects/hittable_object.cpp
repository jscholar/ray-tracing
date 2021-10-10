#include "objects\hittable_object.h"

hittable_object::hittable_object(std::shared_ptr<material> p_material) : p_material{ p_material } {};
