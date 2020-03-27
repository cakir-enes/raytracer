#include "light.h"

#include "material.h"
#include "utils.h"

color phong(const light& l, const hit_record& rec) {
  auto coeff = rec.mat_ptr;

  vec3 N = rec.normal;
  vec3 L = unit_vector(l.pos - rec.p);

  float lambertian = ffmax(dot(N, L), 0.0);
  float specular = [&]() {
    if (lambertian <= 0.0)
      return 0.0;
    vec3 R = reflect(-L, N);
    vec3 V = unit_vector(-rec.p);
    vec3 H = unit_vector(L + V);
    float specAngle = ffmax(dot(N, H), 0.0);
    return pow(specAngle, coeff->shiniess);
  }();

  return coeff->diffuse * lambertian * rec.c + /**/
         coeff->specular * specular * rec.c;
}