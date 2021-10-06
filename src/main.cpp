#include "io/color.h"
#include "physics/vec3.h"
#include "objects/hittable.h"
#include "physics/ray.h"
#include "physics/scattering.h"
#include "physics/math_utils.h"
#include "objects/sphere.h"
#include "objects/hit_list.h"
#include "objects/material.h"

// #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

std::string file_name { "example-image.ppm" };

color ray_color(const ray& r, const hit_list& hittables_list, int bounce) {
	if (bounce <= 3) {
		std::optional<hit_record> possible_hit = hittables_list.find_hit(r, 0.001, 100.0);

		if (possible_hit.has_value()) {
			hit_record hrec = possible_hit.value();

			point3 p = r.at(hrec.t);

			// Get scatter 
			ray s = ray(p, scattering::standard_diffusion(hrec.normal));
			// ray s = ray(p, hrec.object_hit->*p_material->get_bounce_direction(hrec.object_hit->outward_normal_at(p)));

			// Get attenuation

			//cout << "Testing" << endl;
			//cout << hrec.t << endl;
			//cout << hrec.front_hit << endl;
			//cout << hrec.object_hit << endl;
			scattering::standard_diffusion(hrec.normal);
			//cout << (*(hrec.object_hit)).p_material << endl;
			//cout << *(hrec.object_hit->p_material) << endl;
			//cout << (*(hrec.object_hit)).p_material->get_reflectiveness() << endl;
			//cout << "Test complete" << endl;
			//(*((sphere*)hrec.object_hit._Ptr)).p_material
			return 0.5 * ray_color(s, hittables_list, bounce + 1);
			// return hrec.object_hit->p_material->get_reflectiveness() * ray_color(s, hittables_list, bounce + 1);
		}
	}

	// The sky/background color
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(0.0, 0.0, 1.0) + t * color(1.0, 1.0, 1.0);
}

int main() {

	std::ofstream image_file;
	image_file.open(file_name);

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 600;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera
	auto num_samples = 10;
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 2.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Materials
	std::shared_ptr<material> mat_stone = std::make_shared<stone>(stone());
	std::shared_ptr<material> mat_fluorescent = std::make_shared<fluorescent>(fluorescent());
	std::shared_ptr<material> mat_metal = std::make_shared<metal>(metal());

	// Spheres
	// vectorstd::shared_ptr<hittable>> sphere_vec = {};

	// double radius = 0.05;

	// for (double x = -1.0; x <= 1.0; x += 0.5) {
	// 	for (double y = -1.0; y <= 1.0; y += 0.5) {
	// 		for (double z = -3; z >= -8; z -= 1) {
	// 			// cout << "x: " << x << endl;
	// 			// cout << "y: " << y << endl;
	// 			// cout << "z: " << z << endl;
	// 			sphere s = sphere(point3(x, y, z), radius, color(0.0, 1.0, 0.0));
	// 			// cout << s.center << endl;
	// 			sphere_vec.push_back(make_shared<sphere>(s));
	// 			// cout << sphere_vec[0]->center << endl;
	// 			// cout << sphere_vec.size() << endl;
	// 		}
	// 	}
	// }


	// double a = 0;
	// double b = 0.5;
	// double c = -5;
	// double radius2 = 1.0;

	// sphere_vec.push_back(&sphere(point3(a, b, c), radius2, color(0.0, 1.0, 0.0)));
	// sphere_vec.push_back(&sphere(point3(0.25, 0.5, -5), 1.0, color(0.0, 1.0, 0.0)));

	// cout << sphere_vec[0]->center << endl;
	// cout << sphere_vec[1]->center << endl;
	// cout << sphere_vec[2]->center << endl;
	// cout << sphere_vec[3]->center << endl;
	// cout << sphere_vec[4]->center << endl;

	//std::shared_ptr<hittable> sphere1 = make_shared<sphere>(sphere(point3(0, 0, -7.5), 0.5, color(0.0, 1.0, 0.0)));
	std::shared_ptr<hittable> sphere2 = std::make_shared<sphere>(sphere(point3(0, 1, -8.5), 1.5, color(0.0, 1.0, 0.0), mat_metal));
	std::shared_ptr<hittable> sphere3 = std::make_shared<sphere>(sphere(point3(-2.5, 0.5, -10), 1.0, color(0.0, 1.0, 0.0), mat_metal));
	std::shared_ptr<hittable> sphere5 = std::make_shared<sphere>(sphere(point3(0.25, -0.25, -6.5), 0.25, color(0.0, 1.0, 0.0), mat_metal));

	std::shared_ptr<hittable> hill1 = std::make_shared<sphere>(sphere(point3(1.5, -1.25, -4.5), 1.3, color(0.0, 1.0, 0.0), mat_stone));

	std::shared_ptr<hittable> mountain1 = std::make_shared<sphere>(sphere(point3(-25, -15, -30), 30, color(0.0, 1.0, 0.0), mat_stone));

	std::shared_ptr<hittable> moon = std::make_shared<sphere>(sphere(point3(25, 15, -75), 15.0, color(0.0, 1.0, 0.0), mat_fluorescent));
	std::shared_ptr<hittable> earth = std::make_shared<sphere>(sphere(point3(0, -200.5, -1), 200.0, color(0.0, 1.0, 0.0), mat_stone));

	std::vector<std::shared_ptr<hittable>> sphere_vec = { sphere2, sphere3, sphere5, hill1, mountain1, earth, moon };
	hit_list spheres = hit_list(sphere_vec);

	// Render
	image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {

			color stacked_color = color(0, 0, 0);
			for (int sample_number = 0; sample_number < num_samples; ++sample_number) {
				auto u = (i + math_utils::random_double()) / (image_width - 1);
				auto v = (j + math_utils::random_double()) / (image_height - 1);

				ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
				color pixel_color = ray_color(r, spheres, 0);

				stacked_color += pixel_color;
			}

			stacked_color /= num_samples;
			write_color(image_file, stacked_color);
		}
	}

	std::cerr << "\nDone.\n";
}
