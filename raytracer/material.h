//
//  material.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#ifndef material_h
#define material_h
#include "ray.h"

class material {
public:
    virtual bool scatter(
                         const ray& r_in, const hit_record& rec, vec3& attenuation, ray&
                         ) const = 0;
};

#endif /* material_h */
