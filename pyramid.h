//
// Created by Jason on 9/12/2020.
//

#ifndef RAYTRACER_PYRAMID_H
#define RAYTRACER_PYRAMID_H


#include "hittable.h"
#include "vec3.h"

class pyramid : public hittable {
public:
    pyramid() {}
    pyramid(point3 cen, double r, double size, shared_ptr<material> m)
            : center(cen), radius(r), size(size), mat_ptr(m) {};

    virtual bool hit(
            const ray& r, double tmin, double tmax, hit_record& rec) const override;

public:
    point3 center;
    point3 f,g,h,i,j;
    double size;
    double radius;
    shared_ptr<material> mat_ptr;
};

inline bool pyramid::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    //f = point3( 0.0,    0.0, -1.0);

    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}


#endif //RAYTRACER_PYRAMID_H
