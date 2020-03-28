#include "tracer.h"

#include "hittable.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

color trace(const ray& _ray,
            const hittable& world,
            const light& ambient_light,
            const std::vector<light> lights,
            const color& bg_color,
            int depth) {
  hit_record rec;
  ray scattered;

  /**
   * If ray doesn't hit anything or recursion depth is exceeded return
   * background color
   * */

  if (depth > 50 || !world.hit(_ray, 0.001, infinity, rec))
    return bg_color;

  /**
   * Illumunations happened due to lights. Each visible light
   * contrib. to overral color of the point is calculated with
   * Phong model
   * */
  color light_illumunations = [&]() {
    color total =
        ambient_light.intensity * rec.mat_ptr->ambient * rec.mat_ptr->pigment;

    for (const auto& l : lights) {
      if (is_visible(rec.p, l, world)) {
        auto _p = phong(l, rec);
        total += _p;
      }
    }
    return total;
  }();
  /**
   * Depending on the material at the hit point, ray can be
   * reflected and refracted, scattered, each scattered ray
   * traced back to find its contribution to the overral color
   * at the hit/intersection point P.
   * */
  color material_illumunations = [&]() {
    color total = vec3(0., 0., 0.);
    // for (const auto& illum : rec.mat_ptr->scatter(_ray, rec)) {
    //   total += illum.contribution *
    //            trace(illum.scattered, world, lights, bg_color, depth + 1);
    // }
    return total;
  }();
  // Overral color is sum of the illums from lights and material (scattered ray
  // colors)
  color overral_color = light_illumunations + material_illumunations;
  return overral_color;
}

bool is_visible(const vec3& p, const light& l, const hittable& world) {
  hit_record rec;
  auto d = l.pos - p;
  ray r = ray(p, unit_vector(d));
  return world.hit(r, 0.001, d.length(), rec);
}