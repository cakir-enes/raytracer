//
//  sphere.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere(vec3 cen, double r) : center(cen), radius(r) {};
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    
public:
    vec3 center;
    double radius;
};

#endif /* sphere_h */
