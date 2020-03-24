//
//  material.h
//  raytracer
//
//  Created by Enes Cakir on 24.03.2020.
//  Copyright © 2020 lymitshn. All rights reserved.
//

#ifndef material_h
#define material_h
#include "hittable.h"
#include "ray.h"

class material {
public:
    virtual bool scatter(
                         const ray& r_in, const hit_record& rec, vec3& attenuation, ray&
                         ) const = 0;
};



namespace materials {
double schlick(double cosine, double ref_idx);
class lambertian : public material {
public:
    lambertian(const vec3& a) : albedo(a) {}
    
    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
    
public:
    vec3 albedo;
};
    
class metal : public material {
public:
    metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
    
    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
    
public:
    vec3 albedo;
    double fuzz;
};
    
    class dielectric : public material {
    public:
        double ref_idx;
        dielectric(double ri) : ref_idx(ri) { }
        
        bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
    };
    
}; // namespace materials

#endif /* material_h */
