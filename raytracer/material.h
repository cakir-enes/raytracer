//
//  material.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#ifndef material_h
#define material_h
#include "hittable.h"
#include "ray.h"

namespace materials {

struct illumunation {
  ray scattered;
  color contribution;
};

class material {
 public:
  virtual std::vector<illumunation> scatter(const ray& r_in,
                                            const hit_record& rec) const = 0;
};

double schlick(double cosine, double ref_idx);

struct surface {
  float ambient;
  float diffuse;
  float specular;
  float shiniess;
  float reflectivity;
};

class custom : public material {
 public:
  custom(surface s) : _surface(s){};

  std::vector<illumunation> scatter(const ray& r_in, const hit_record& rec);

 private:
  surface _surface;
};
}  // namespace materials

#endif /* material_h */
