//
//  material.cpp
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#include "material.h"

namespace materials {
    bool lambertian::scatter(
                         const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
                         ) const {
        vec3 scatter_dir = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }
    
    bool metal::scatter(
                             const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
                             ) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};
