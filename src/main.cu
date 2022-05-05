#include "io/color.h"
#include "physics/vec3.cuh"
#include "physics/ray.cuh"
#include "physics/scattering.cuh"
#include "physics/math_utils.cuh"
#include "physics/ray_tracer.cuh"
#include "objects/hittable.cuh"
#include "objects/sphere.cuh"
#include "objects/hit_list.cuh"
#include "objects/material.cuh"
#include "objects/sphere.cuh"

#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <driver_types.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>


std::string file_name{ "example-image.ppm" };

int main() {

	std::ofstream image_file;
	image_file.open(file_name);

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1920;
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
	auto mat_stone = std::make_shared<stone>();
	auto mat_grass = std::make_shared<grass>();
	auto mat_ocean = std::make_shared<ocean>();
	auto mat_fluorescent = std::make_shared<fluorescent_white>();
	auto mat_gold = std::make_shared<gold>();
	auto mat_metal = std::make_shared<metal>();

	std::shared_ptr<sphere> sphere2 = std::make_shared<sphere>(sphere(point3(0, 1, -8.5), 1.5, color(0.0, 1.0, 0.0), mat_gold));
	std::shared_ptr<sphere> sphere3 = std::make_shared<sphere>(sphere(point3(-2.5, 0.5, -10), 1.0, color(0.0, 1.0, 0.0), mat_metal));
	std::shared_ptr<sphere> sphere5 = std::make_shared<sphere>(sphere(point3(0.25, -0.25, -6.5), 0.25, color(0.0, 1.0, 0.0), mat_metal));

	std::shared_ptr<sphere> hill1 = std::make_shared<sphere>(sphere(point3(3.5, -1.25, -4.5), 1.3, color(0.0, 1.0, 0.0), mat_grass));

	std::shared_ptr<sphere> mountain1 = std::make_shared<sphere>(sphere(point3(-25, -15, -30), 30, color(0.0, 1.0, 0.0), mat_stone));

	std::shared_ptr<sphere> moon = std::make_shared<sphere>(sphere(point3(25, 15, -75), 15.0, color(0.0, 1.0, 0.0), mat_fluorescent));
	std::shared_ptr<sphere> moon2 = std::make_shared<sphere>(sphere(point3(55, 23, -75), 5.0, color(0.0, 1.0, 0.0), mat_metal));
	std::shared_ptr<sphere> earth = std::make_shared<sphere>(sphere(point3(0, -200.5, -1), 200.0, color(0.0, 1.0, 0.0), mat_ocean));

	std::vector<std::shared_ptr<hittable>> sphere_vec = { sphere2, sphere3, sphere5, hill1, mountain1, earth, moon, moon2 };
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
				color pixel_color = ray_tracer::ray_color(r, spheres, 0);

				stacked_color += pixel_color;
			}

			stacked_color /= num_samples;
			write_color(image_file, stacked_color);
		}
	}

	std::cerr << "\nDone.\n";
}
