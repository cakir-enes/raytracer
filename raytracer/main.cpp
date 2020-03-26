//
//  main.cpp
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#include <iostream>

#include "camera.h"
#include "hittable_list.hpp"
#include "material.h"
#include "sphere.h"
#include "utils.h"

using namespace materials;

vec3 ray_color(const ray& r, const hittable& world, int depth) {
  hit_record rec;

  if (depth <= 0)
    return vec3(0, 0, 0);
  // Generates random diffuse bounce ray on hit
  if (world.hit(r, 0.001, infinity,
                rec)) {  // min = 0.001 to avoid shadow acne problem
    //        vec3 target = rec.p + rec.normal + random_unit_vector();
    ray scattered;
    vec3 attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);
    return vec3(0, 0, 0);
  }
  vec3 unit_dir = unit_vector(r.direction());
  auto t = 0.5 * (unit_dir.y() + 1.0);
  return (1.0 - t) * vec3(1., 1., 1.) + t * vec3(0.5, 0.7, 1.);
}

hittable_list random_scene() {
  hittable_list world;

  world.add(make_shared<sphere>(vec3(0, -1000, 0), 1000,
                                make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = vec3::random() * vec3::random();
          world.add(make_shared<sphere>(center, 0.2,
                                        make_shared<lambertian>(albedo)));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = vec3::random(.5, 1);
          auto fuzz = random_double(0, .5);
          world.add(make_shared<sphere>(center, 0.2,
                                        make_shared<metal>(albedo, fuzz)));
        } else {
          // glass
          world.add(
              make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
        }
      }
    }
  }

  world.add(
      make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));

  world.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0,
                                make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

  world.add(make_shared<sphere>(vec3(4, 1, 0), 1.0,
                                make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

  return world;
}

int main(int argc, const char* argv[]) {
  const int image_width = 200;
  const int image_height = 100;
  const auto aspect_ratio = double(image_width) / image_height;
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  //   vec3 lower_left_corner(-2.0, -1.0, -1.0);
  //   vec3 horizontal(4.0, 0.0, 0.0);
  //   vec3 vertical(0.0, 2.0, 0.0);
  //   vec3 origin(0.0, 0.0, 0.0);

  //   hittable_list world;

  //   vec3 lookfrom(3, 3, 2);
  //   vec3 lookat(0, 0, -1);
  //   vec3 vup(0, 1, 0);
  //   auto dist_to_focus = (lookfrom - lookat).length();
  //   auto aperture = 2.0;

  //   camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,
  //   dist_to_focus);

  auto world = random_scene();

  vec3 lookfrom(13, 2, 3);
  vec3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;
  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

  auto R = cos(pi / 4);

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
      vec3 color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / image_width;
        auto v = (j + random_double()) / image_height;
        ray r = cam.get_ray(u, v);
        color += ray_color(r, world, max_depth);
      }
      color.write_color(std::cout, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}
