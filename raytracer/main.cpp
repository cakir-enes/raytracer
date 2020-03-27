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
#include <vector>

#include "camera.h"
#include "hittable_list.hpp"
#include "light.h"
#include "material.h"
#include "sphere.h"
#include "tracer.h"
#include "utils.h"

using namespace materials;

int main(int argc, const char* argv[]) {
  const int image_width = 200;
  const int image_height = 100;
  const auto aspect_ratio = double(image_width) / image_height;
  const int samples_per_pixel = 100;
  const int max_depth = 50;
  const color bg_color(0, 0, 0);

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  hittable_list world;
  std::vector<std::reference_wrapper<light>> lights;

  vec3 lookfrom(13, 2, 3);
  vec3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;
  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

  auto R = cos(pi / 4);

  // world.add(make_shared<sphere>(vec3(0, 0, -1)));

  //   world.add(make_shared<sphere>(
  //       vec3(0, 0, -1), 0.5,
  //       make_shared<materials::lambertian>(vec3(0.1, 0.2, 0.5))));
  //   world.add(make_shared<sphere>(
  //       vec3(0, -100.5, -1), 100,
  //       make_shared<materials::lambertian>(vec3(0.8, 0.8, 0.0))));
  //   world.add(make_shared<sphere>(
  //       vec3(1, 0, -1), 0.5,
  //       make_shared<materials::metal>(vec3(0.8, 0.6, 0.2), 0.3)));
  //   world.add(make_shared<sphere>(vec3(-1, 0, -1), 0.5,
  //                                 make_shared<materials::dielectric>(1.5)));
  //   world.add(make_shared<sphere>(vec3(-1, 0, -1), -0.45,
  //                                 make_shared<materials::dielectric>(1.5)));

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color c(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / image_width;
        auto v = (j + random_double()) / image_height;
        ray r = cam.get_ray(u, v);
        c += trace(r, world, lights, bg_color, max_depth);
      }
      c.write_color(std::cout, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}
