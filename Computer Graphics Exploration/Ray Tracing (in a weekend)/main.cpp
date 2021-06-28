// #include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rtweekend.h"

#include "color.h"
#include "sphere.h"
#include "hit_list.h"

using namespace std;

string file_name = "test-image.ppm";

color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 0.0, 0.0) + t * color(0.0, 0.0, 1.0);
}

int main() {

	ofstream image_file;
	image_file.open(file_name);

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera
	auto num_samples = 500;
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Spheres
	hittable* sphere1 = &sphere(point3(0, 0.5, -5), 1.0, color(0.0, 1.0, 0.0));
	hittable* sphere2 = &sphere(point3(0, 2.5, -7), 3.0, color(0.0, 1.0, 0.0));
	hittable* sphere3 = &sphere(point3(-5, -5, -10), 4.0, color(0.0, 1.0, 0.0));
	hittable* earth = &sphere(point3(0, -100.5, -1), 100.0, color(0.0, 1.0, 0.0));

	vector<hittable*> sphereVec = { sphere1, sphere2, sphere3, earth };
	hit_list spheres = hit_list(sphereVec);

	// Render

	image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {

			color stacked_color = color(0, 0, 0);
			for (int sample_number = 0; sample_number < num_samples; ++sample_number) {
				auto u = (i + random_double() ) / (image_width - 1);
				auto v = (j + random_double() ) / (image_height - 1);



				ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

				hit_record hrec;
				color pixel_color;

				bool did_hit = spheres.find_hit(r, 0.0, 100.0, hrec);

				if (did_hit) {
					// calculate pixel color
					pixel_color = vec3(1, 1, 1) + hrec.normal;
					pixel_color /= 2;
				}
				else {
					pixel_color = ray_color(r);
				}

				stacked_color += pixel_color;
			}

			stacked_color /= num_samples;
			write_color(image_file, stacked_color);
		}
	}

	std::cerr << "\nDone.\n";
}

string progress_bar() {
	return "";
}
