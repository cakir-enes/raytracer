

#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>

#include "parser.h"
#include "tracer.h"
#include "utils.h"


int main(int argc, const char* argv[]) {

    std::string file;
    int samples_per_pixel = 1;
    if (argc == 1) {
        std::cerr << "Please specify input path. ./main <filename> \n";
        return -1;
    } else {
        file = argv[1];
        if (argc > 2) {
            samples_per_pixel = atoi(argv[2]);
        }
    }

    std::ofstream out;
    auto opts = parse_options(file);
    out.open(opts.output_name, std::ios::out | std::ios::binary);


    const color bg_color(0.5, 0.5, 0.5);

    out << "P3\n" << opts.width << ' ' << opts.height << "\n255\n";

    for (int j = opts.height - 1; j >= 0; --j) {
        std::cerr << "\rRemaining: " << j << ' ' << std::flush;
        for (int i = 0; i < opts.width; ++i) {
            color c(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / opts.width;
        auto v = (j + random_double()) / opts.height;
        ray r = opts.cam.get_ray(u, v);
        c += trace(r, opts.objects, opts.ambient_light, opts.lights, bg_color, 0);
      }
      c.write_color(out, samples_per_pixel);
    }
  }
  out.flush();
  out.close();
  std::cerr << "\nDone.\n";
}
