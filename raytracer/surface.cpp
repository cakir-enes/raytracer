
#include "surface.h"

/**
 * Returns all scattered rays caused by given ray at hit point.
 */
std::vector<illumunation> surface::scatter(const ray &r_in,
                                           const hit_record &rec) const {
    std::vector<illumunation> ilms;
    auto reflection = [&]() {
        if (rec.mat_ptr->reflectivity <= 0)
            return false;

        vec3 reflected = reflect(r_in.direction(), rec.normal);
        ray scattered = ray(rec.p, reflected);
        illumunation i;
        i.contribution = rec.mat_ptr->reflectivity;
        i.scattered = scattered;
        ilms.push_back(i);
        return true;
    }();

    auto refraction = [&]() {
        auto s = rec.mat_ptr;
        if (s->transparency <= 0.)
            return false;

        double etai_over_etat = (rec.front_face) ? (1.0 / s->ior) : (s->ior);
        illumunation i;
        i.contribution = s->transparency;
        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        i.scattered = [&]() {
            bool must_reflect = etai_over_etat * sin_theta > 1.0;
            if (must_reflect) {
                vec3 reflected = reflect(unit_direction, rec.normal);
                return ray(rec.p, reflected);
            }
            vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
            return ray(rec.p, refracted);
        }();

        ilms.push_back(i);
        return true;
    }();
    return ilms;
}