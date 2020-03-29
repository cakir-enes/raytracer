//
//  material.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#pragma once
#include "hittable.h"
#include "ray.h"

struct illumunation {
    ray scattered;
    float contribution;
};

struct surface {
    float ambient;
    float diffuse;
    float specular;
    float shiniess;
    float reflectivity;
    color pigment;

    friend std::istream& operator>>(std::istream& str, surface& s) {
        return str >> s.ambient >> s.diffuse >> s.specular >> s.shiniess >>
                   s.reflectivity;
    }

    std::vector<illumunation> scatter(const ray& r_in,
                                      const hit_record& rec) const;
};

double schlick(double cosine, double ref_idx);


