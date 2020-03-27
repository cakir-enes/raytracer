#ifndef light_h
#define light_h

#include "hittable.h"
#include "vec3.h"

struct light {
  vec3 pos;
  color intensity;
  float a;
  float b;
  float c;
};

color phong(const light& l, const hit_record& rec);

#endif /* light_h */
