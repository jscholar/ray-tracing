#include "physics/ray_tracer.h"

#include "physics/vec3.h"
#include "physics/ray.h"
#include "physics/scattering.h"
#include "objects/hittable.h"
#include "objects/hittable_object.h"
#include "objects/material.h"

#include <memory>
#include <algorithm>

color ray_tracer::ray_color(const ray& r, const hittable& hittable_entity, int bounce) {
	if (bounce <= 3) {
		std::optional<hit_record> possible_hit = hittable_entity.find_hit(r, 0.001, 100.0);

		if (possible_hit.has_value()) {
			hit_record hrec = possible_hit.value();
			point3 p = r.at(hrec.t);

			// Get scatter 
			std::shared_ptr<material> mat = hrec.object_hit->p_material;
			ray s = ray(p, mat->get_bounce_direction(r.dir, hrec.normal));


			// ray s = ray(p, hrec.object_hit->*p_material->get_bounce_direction(hrec.object_hit->outward_normal_at(p)));

			// Get attenuation
			double attenuation = mat->get_reflectiveness();

			//cout << "Testing" << endl;
			//cout << hrec.t << endl;
			//cout << hrec.front_hit << endl;
			//cout << hrec.object_hit << endl;
			//cout << (*(hrec.object_hit)).p_material << endl;
			//cout << *(hrec.object_hit->p_material) << endl;
			//cout << (*(hrec.object_hit)).p_material->get_reflectiveness() << endl;
			//cout << "Test complete" << endl;
			//(*((sphere*)hrec.object_hit._Ptr)).p_material
			color new_color = ray_color(s, hittable_entity, bounce + 1);
			new_color[0] = std::clamp(new_color[0], 0.0, 1.0);
			new_color[1] = std::clamp(new_color[1], 0.0, 1.0);
			new_color[2] = std::clamp(new_color[2], 0.0, 1.0);
			
			return attenuation * new_color;
			// return hrec.object_hit->p_material->get_reflectiveness() * ray_color(s, hittable_entity, bounce + 1);
		}
	}

	// The sky/background color
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(0.08, 0.08, 0.15) + t * color(0.08, 0.08, 0.08);
}

vec3 ray_tracer::ray_scatter(vec3& incoming_direction, const material& material_hit, vec3& surface_normal) {
	return vec3();
}