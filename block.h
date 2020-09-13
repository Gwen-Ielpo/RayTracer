//
// Created by Jason on 9/12/2020.
//

#ifndef BLOCK_H
#define BLOCK_H

#include "rtweekend.h"

#include "rectangle.h"
#include "hittable_list.h"

class block : public hittable  {
public:
    block() {}
    block(const point3& p0, const point3& p1, shared_ptr<material> ptr);

    virtual bool hit(const ray& r, double t0, double t1, hit_record& rec) const override;



public:
    point3 block_min;
    point3 block_max;
    hittable_list sides;
};

inline block::block(const point3& p0, const point3& p1, shared_ptr<material> ptr) {
    block_min = p0;
    block_max = p1;

    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

inline bool block::hit(const ray& r, double t0, double t1, hit_record& rec) const {
    return sides.hit(r, t0, t1, rec);
}

#endif
