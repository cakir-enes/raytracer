#include "light.h"


#include <cmath>

#include "material.h"
#include "utils.h"
#include "vec3.h"

color phong(const light& l, const hit_record& rec) {
  auto coeff = rec.mat_ptr;

  vec3 L = unit_vector(l.pos - rec.p);  // to light src
  vec3 V = unit_vector(-rec.p);         // to viewer
  vec3 N = rec.normal;                  // normal
  vec3 H = unit_vector(L + V);          // halfway

  auto K = rec.mat_ptr;
  auto dist = (l.pos - rec.p).length();
  auto attenuation =  (l.a  + l.b * dist + l.c * dist * dist);

  auto diffuse = rec.mat_ptr->pigment * K->diffuse * ffmax(0, dot(L, N));
  auto specular = K->specular * pow(ffmax(0, dot(H, N)), double(K->shiniess));

    return l.intensity / attenuation * vec3(diffuse.x() + specular, diffuse.y() + specular, diffuse.z() + specular);
//  return rec.mat_ptr->pigment * K->ambient * l.intensity +
//         (diffuse + specular) * attenuation;
}