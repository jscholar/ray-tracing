#include "io/color.h"

#include "physics/vec3.cuh"

#include <iostream>
#include <algorithm>


void write_color(std::ostream& out, color pixel_color) {
	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(255.999 * std::clamp(sqrt(pixel_color.x()), 0.0, 1.0)) << ' '
		<< static_cast<int>(255.999 * std::clamp(sqrt(pixel_color.y()), 0.0, 1.0)) << ' '
		<< static_cast<int>(255.999 * std::clamp(sqrt(pixel_color.z()), 0.0, 1.0)) << '\n';
}
