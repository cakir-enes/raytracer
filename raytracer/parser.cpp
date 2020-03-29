#include "parser.h"

#include <fstream>

#include "sphere.h"

options parse_options(std::string filename) {
  std::ifstream in(filename);
  if (!in.is_open())
    return options{};

  auto out_name = [&in]() {
    std::string out;
    getline(in, out);
    return out;
  }();

  auto dims = [&in]() {
    int w, h;
    in >> w >> h;
    return std::pair<int, int>(w, h);
  }();

  auto cam = [&in, &dims]() {
    vec3 eye, at, up;
    double fov_y;
    in >> eye >> at >> up >> fov_y;
    return camera(eye, at, up, fov_y, double(dims.first) / dims.second);
  }();

  auto lights = [&in]() {
    int n;
    std::vector<light> lights;
    vec3 pos, intensity;
    float a, b, c;
    in >> n;
    for (int i = 0; i < n; i++) {
      in >> pos >> intensity >> a >> b >> c;
      lights.push_back(light{pos, intensity, a, b, c});
    }
    return lights;
  }();
  std::cerr << "LIGHT SIZE " << lights.size() << "\n";
  auto pigments = [&in]() {
    int numP;
    std::string type;
    std::vector<color> colors;
    in >> numP;
    color c;
    for (int i = 0; i < numP; i++) {
      in >> type >> c;
      colors.push_back(c);
    }
    return colors;
  }();
  std::cerr << "PIGMENT SIZE " << pigments.size() << "\n";
  auto surfaces = [&in]() {
    std::vector<surface> surfaces;
    int numF;
    surface s;
    in >> numF;
    for (int i = 0; i < numF; i++) {
      in >> s;
      surfaces.push_back(s);
    }
    return surfaces;
  }();
  std::cerr << "SURFACES SIZE " << pigments.size() << "\n";
  auto objects = [&]() {
    hittable_list world;
    int n, pigment_idx, surface_idx;
    in >> n;
    std::string type;
    vec3 pos;
    float radius;
    for (int i = 0; i < n; i++) {
      in >> pigment_idx >> surface_idx >> type >> pos >> radius;
      auto s = surfaces[surface_idx];
      s.pigment = pigments[pigment_idx];
      world.add(make_shared<sphere>(pos, radius, s));
    }
    return world;
  }();
  std::cerr << "WORLD SIZE " << objects.objects.size() << "\n";
  light ambient = lights[0];
  lights.erase(lights.begin());

  return options{out_name, dims.first, dims.second, cam,
                 ambient,  lights,     objects};
};