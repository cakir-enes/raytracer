
#pragma once

#include "hittable.h"
#include "surface.h"
#include "vec3.h"

class sphere : public hittable {
 public:
  sphere(vec3 cen, double r, surface m)
      : center(cen), radius(r), mat_ptr(m){};

  virtual bool hit(const ray& r,
                   double t_min,
                   double t_max,
                   hit_record& rec) const;

 public:
  vec3 center;
  double radius;
  surface mat_ptr;
};
