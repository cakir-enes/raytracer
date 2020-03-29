//
//  camera.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#pragma once
#include "utils.h"

class camera {
 public:
  camera() = default;
  camera(vec3 eye, vec3 lookat, vec3 vup, double vfov, double aspect) {
    origin = eye;
    vec3 z, x, y;

    auto theta = degrees_to_radians(vfov);
    auto half_height = tan(theta / 2);
    auto half_width = aspect * half_height;
    z = unit_vector(eye - lookat);
    x = unit_vector(cross(vup, z));
    y = cross(z, x);

    lower_left_corner = origin - half_width * x - half_height * y - z;

    horizontal = 2 * half_width * x;
    vertical = 2 * half_height * y;
  }

  ray get_ray(double s, double t) {
    return {origin,
               lower_left_corner + s * horizontal + t * vertical - origin};
  }

 public:
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};