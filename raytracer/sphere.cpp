//
//  sphere.cpp
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#include "sphere.h"

#include <memory>

#include "material.h"

bool sphere::hit(const ray &r,
                 double t_min,
                 double t_max,
                 hit_record &rec) const {

    auto fill_rec = [&](float t, bool inside) {
        if (t > t_max || t < t_min)
            return false;
        rec.t = t;
        rec.p = r.at(t);
        auto outward_normal = (rec.p - center) / radius;
//        rec.normal = (inside ? -1 : 1) * outward_normal;
        rec.front_face = inside;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = std::make_shared<materials::surface>(mat_ptr);
        return true;
    };

    vec3 oc = r.origin() - center;
    float a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    auto root = sqrt(discriminant);
    auto sol1 = (-half_b - root) / a;
    auto sol2 = (-half_b + root) / a;
    auto inside = (sol1 < 0 && sol2 > 0) || (sol1 > 0 && sol2 < 0);
    return fill_rec(sol1, inside) || fill_rec(sol2, inside);

// SOMEHWAT

//    vec3 oc = r.origin() - center;
//    float a = dot(r.direction(), r.direction());
//    float b = 2.0 * dot(oc, r.direction());
//    float c = dot(oc,oc) - radius*radius;
//    float discriminant = b*b - 4*a*c;
//    if(discriminant < 0.0){
//        return false;
//    }
//    else{
//        float numerator = -b - sqrt(discriminant);
//        if (numerator > 0.0) {
//            return fill_rec(numerator / (2.0 * a), true);
//        }
//
//        numerator = -b + sqrt(discriminant);
//        if (numerator > 0.0) {
//            return fill_rec(numerator / (2.0 * a), false);
//        }
//        else {
//            return false;
//        }
//
//    }


//    auto u  = r.origin() - center;
//    auto d = r.direction();
//    auto temp = (u - dot(d, u) * d).length_squared();
//    auto disc = 4 * (radius * radius - temp);
//    if (disc < 0)
//        return false;
//    auto sol1 = dot(d, u) - sqrt(radius * radius - temp);
//    auto sol2 = dot(d, u) + sqrt(radius * radius - temp);
//    auto inside = (sol1 < 0 && sol2 > 0) || (sol1 > 0 && sol2 < 0);
//    return fill_rec(sol1, true) || fill_rec(sol2, true);
}

