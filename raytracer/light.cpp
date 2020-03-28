#include "light.h"

#include <math.h>

#include <cmath>

#include "material.h"
#include "utils.h"
#include "vec3.h"

color phong(const light& l, const hit_record& rec) {
  auto coeff = rec.mat_ptr;

  vec3 L = unit_vector(l.pos - rec.p);   // to light src
  vec3 V = unit_vector(-rec.p);          // to viewer
  vec3 N = unit_vector(rec.normal);      // normal
  vec3 R = unit_vector(reflect(-L, N));  // perfect feclector
  vec3 H = unit_vector(L + V);           // halfway

  auto K = rec.mat_ptr;
  auto dist = (l.pos - rec.p).length();
  auto attenuation = 1 / (l.a * dist + l.b * dist + l.c * pow(dist, 2));
  auto diffuse = K->diffuse * l.intensity * ffmax(0, dot(N, L));
  auto specular =
      K->specular * l.intensity * pow(ffmax(0, dot(H, N)), K->shiniess);

  return (K->ambient * l.intensity + (diffuse + specular) / attenuation);
}