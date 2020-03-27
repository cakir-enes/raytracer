#include "parser.h"

#include <fstream>

#include "sphere.h"

options parse_objects(std::string filename) {
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
    vec3 pos, at, up;
    double fov_y;
    in >> pos >> at >> up >> fov_y;
    return camera(pos, at, up, fov_y, double(dims.first) / dims.second, 2.0,
                  1.0);
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

  auto surfaces = [&in]() {
    std::vector<materials::surface> surfaces;
    int numF;
    materials::surface s;
    for (int i = 0; i < numF; i++) {
      in >> s;
      surfaces.push_back(s);
    }
    return surfaces;
  }();

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

  light ambient = lights[0];
  lights.erase(lights.begin());

  return options{out_name, dims.first, dims.second, cam,
                 ambient,  lights,     objects};
};

class parser {
 public:
 private:
  /**
   * pos [x y z] intensity [r g b] attenuation [a bd cd^2]
   * 1st line is AMBIENT LIGHTING
   * returns <ambient light, lights>
   * */
  void parse_lights();

  /**
   * # pigments [numP]
   * [r g b]
   * */
  void parse_pigments();

  /**
   * # surfaces [numF]
   * K_ambient K_diffuse K_specular shiness reflectiviy
   * */
  void parse_surfaces();

 private:
  std::vector<materials::surface> surfaces;
  std::vector<color> pigments;
  light ambient_light;
};