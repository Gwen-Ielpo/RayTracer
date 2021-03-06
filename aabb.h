//
// Created by Jason on 9/12/2020.
//


#ifndef AABB_H
#define AABB_H

#include "rtweekend.h"

class aabb {
public:
    aabb() {}
    aabb(const point3& a, const point3& b) { _min = a; _max = b;}

    point3 min() const {return _min; }
    point3 max() const {return _max; }

    bool hit(const ray& r, double tmin, double tmax) const {
        for (int a = 0; a < 3; a++) {
            auto t0 = fmin((_min[a] - r.origin()[a]) / r.direction()[a],
                           (_max[a] - r.origin()[a]) / r.direction()[a]);
            auto t1 = fmax((_min[a] - r.origin()[a]) / r.direction()[a],
                           (_max[a] - r.origin()[a]) / r.direction()[a]);
            tmin = fmax(t0, tmin);
            tmax = fmin(t1, tmax);
            if (tmax <= tmin)
                return false;
        }
        return true;
    }

    point3 _min;
    point3 _max;
};

#endif


