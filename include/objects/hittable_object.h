#pragma once

#include <memory>

#include "physics/vec3.h"
#include "objects/hittable.h"

class hittable_object;
class material;

/**
 * @brief Representation of a single geometric hittable object (such as a sphere)
*/
class hittable_object : public std::enable_shared_from_this<hittable_object>, public hittable {
public:
	std::shared_ptr<material> p_material;

	virtual vec3 outward_normal_at(const point3& point) const = 0;
	virtual color get_color_at(const point3& point) const = 0;
};
