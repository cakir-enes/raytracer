#include "sphere.h"

#include <memory>

#include "surface.h"

bool sphere::hit(const ray &r,
                 double t_min,
                 double t_max,
                 hit_record &rec) const {

    auto fill_rec = [&](float t) {
        if (t > t_max || t < t_min)
            return false;
        rec.t = t;
        rec.p = r.at(t);
        auto outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = std::make_shared<surface>(mat_ptr);
        return true;
    };

    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    auto root = sqrt(discriminant);
    auto sol1 = (-half_b - root) / a;
    auto sol2 = (-half_b + root) / a;
    // If first solution satisfies conds, it will return immediately due to short-circuit evaluation.
    return fill_rec(sol1) || fill_rec(sol2);
}

