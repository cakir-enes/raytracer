//
//  main.cpp
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <istream>
#include <vector>

#include "camera.h"
#include "hittable_list.hpp"
#include "light.h"
#include "material.h"
#include "parser.h"
#include "sphere.h"
#include "tracer.h"
#include "utils.h"
using namespace materials;

int main(int argc, const char* argv[]) {

  std::string file = "/Users/ecakir/Desktop/Projectz/raytracer/raytracer/test2.in";
  std::ofstream out;
  auto p = parse_options(file);
  out.open("out.ppm", std::ios::out | std::ios::binary);
  const int samples_per_pixel = 1;
  const int max_depth = 50;

  const color bg_color(0.5, 0.5, 0.5);

  out << "P3\n" << p.width << ' ' << p.height << "\n255\n";

  for (int j = p.height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < p.width; ++i) {
      color c(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / p.width;
        auto v = (j + random_double()) / p.height;
        ray r = p.cam.get_ray(u, v);
        c += trace(r, p.objects, p.ambient_light, p.lights, bg_color, 0);
      }
      c.write_color(out, samples_per_pixel);
    }
  }
  out.flush();
  out.close();
  std::cerr << "\nDone.\n";
}
