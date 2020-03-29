

#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>

#include "parser.h"
#include "tracer.h"
#include "utils.h"


int main(int argc, const char* argv[]) {

  std::string file = "/Users/ecakir/Desktop/Projectz/raytracer/raytracer/test2reflective.in";
  std::ofstream out;
    auto opts = parse_options(file, false);
  out.open("out.ppm", std::ios::out | std::ios::binary);
    const int samples_per_pixel = 1;
//  const int max_depth = 50;

  const color bg_color(0.5, 0.5, 0.5);

  out << "P3\n" << opts.width << ' ' << opts.height << "\n255\n";

  for (int j = opts.height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < opts.width; ++i) {
      color c(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / opts.width;
        auto v = (j + random_double()) / opts.height;
        ray r = opts.cam.get_ray(u, v);
        c += trace(r, opts.objects, opts.ambient_light, opts.lights, bg_color, 0);
      }
      c.write_color(out, samples_per_pixel);
    }
  }
  out.flush();
  out.close();
  std::cerr << "\nDone.\n";
}
