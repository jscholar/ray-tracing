#include "physics/ray_tracer.cuh"

#include "physics/vec3.cuh"
#include "physics/ray.cuh"
#include "physics/scattering.cuh"
#include "objects/hittable.cuh"
#include "objects/hittable_object.cuh"
#include "objects/material.cuh"

#include <memory>
#include <algorithm>
#include <cuda_runtime.h>

color ray_tracer::ray_color(const ray& r, const hittable& hittable_entity, int bounce) {
	if (bounce <= 5) {
		std::optional<hit_record> possible_hit = hittable_entity.find_hit(r, 0.001, 100.0);

		if (possible_hit.has_value()) {
			hit_record hrec = possible_hit.value();
			point3 p = r.at(hrec.t);

			// Get scatter 
			std::shared_ptr<material> mat = hrec.object_hit->p_material;
			ray s = ray(p, mat->get_bounce_direction(r.dir, hrec.normal));


			// ray s = ray(p, hrec.object_hit->*p_material->get_bounce_direction(hrec.object_hit->outward_normal_at(p)));

			// Get attenuation
			color attenuating_color = mat->get_reflectiveness();

			color new_color = ray_color(s, hittable_entity, bounce + 1);

			// Prevents white speckles
			new_color[0] = std::clamp(new_color[0], 0.0, 1.0);
			new_color[1] = std::clamp(new_color[1], 0.0, 1.0);
			new_color[2] = std::clamp(new_color[2], 0.0, 1.0);
			
			return attenuating_color * new_color;
			// return hrec.object_hit->p_material->get_reflectiveness() * ray_color(s, hittable_entity, bounce + 1);
		}
	}

	// The sky/background color
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(0.08, 0.08, 0.25) + t * color(0.08, 0.08, 0.15);
}

vec3 ray_tracer::ray_scatter(vec3& incoming_direction, const material& material_hit, vec3& surface_normal) {
	return vec3();
}