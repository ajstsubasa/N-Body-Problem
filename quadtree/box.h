#pragma once

#include "vector2.h"

namespace quadtree {

template <typename T> class Box {
  public:
    PVector<T> topLeft;
    PVector<T> bottomRight;

    bool contains(const PVector<T> &p) const { return (p.x >= topLeft.x && p.x < bottomRight.x && p.y >= topLeft.y && p.y < bottomRight.y); }

    std::array<Box<T>, 4> subdivide() const {
        const T mx = (topLeft.x + bottomRight.x) / 2;
        const T my = (topLeft.y + bottomRight.y) / 2;

        return {
            Box<T>{{topLeft.x, topLeft.y}, {mx, my}},        // TL: [lx,mx) x [ty,my)
            Box<T>{{mx, topLeft.y}, {bottomRight.x, my}},    // TR: [mx,rx) x [ty,my)
            Box<T>{{topLeft.x, my}, {mx, bottomRight.y}},    // BL: [lx,mx) x [my,by)
            Box<T>{{mx, my}, {bottomRight.x, bottomRight.y}} // BR: [mx,rx) x [my,by)
        };
    }
};

} // namespace quadtree
