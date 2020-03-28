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
  camera(){};
  camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect) {
    origin = lookfrom;
    vec3 u, v, w;

    auto theta = degrees_to_radians(vfov);
    auto half_height = tan(theta / 2);
    auto half_width = aspect * half_height;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    lower_left_corner = origin - half_width * u - half_height * v - w;

    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
  }

  ray get_ray(double s, double t) {
    return ray(origin,
               lower_left_corner + s * horizontal + t * vertical - origin);
  }

 public:
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};