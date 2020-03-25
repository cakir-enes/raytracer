//
//  ray.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#ifndef ray_h
#define ray_h
#include "vec3.h"

class ray {
 public:
  ray() {}
  ray(const vec3& origin, const vec3& direction)
      : orig(origin), dir(direction) {}

  vec3 origin() const { return orig; }
  vec3 direction() const { return dir; }
  vec3 at(double t) const { return orig + t * dir; }

 public:
  vec3 orig;
  vec3 dir;
};

#endif /* ray_h */
