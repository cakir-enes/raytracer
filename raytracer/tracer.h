#pragma once
#include <vector>

#include "hittable.h"
#include "light.h"
#include "ray.h"

bool is_visible(const vec3& pos, const light& l, const hittable& world);

color trace(const ray& _ray,
            const hittable& world,
            const std::vector<std::reference_wrapper<light>> lights,
            const color& bg_color,
            int depth);