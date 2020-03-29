#pragma once

#include <string>

#include "camera.h"
#include "hittable_list.hpp"
#include "light.h"
#include "surface.h"

struct options {
  std::string output_name;
  int width;
  int height;
  camera cam;
  light ambient_light;
  std::vector<light> lights;
  hittable_list objects;
};

options parse_options(std::string filename);
