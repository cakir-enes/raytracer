//
//  hittable.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#ifndef hittable_h
#define hittable_h

#include "utils.h"
#include "ray.h"

class material;

struct hit_record {
    double t;
    vec3 p; // hit point
    shared_ptr<material> mat_ptr;
    vec3 normal;
    bool front_face;
    
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
    
};

// All hittable objects must extend this, used for calculating hit points, normals
class hittable {
public:
    virtual bool hit(const ray&, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif /* hittable_h */
