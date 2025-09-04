#include "quadtree/vector2.h"
#include <cstdint>
#pragma once
struct Body {
  public:
    quadtree::PVector<double> position;
    quadtree::PVector<double> velocity;
    double radius;
    double center_of_mass;

    Body(double x, double y, double radius, double center_of_mass) {
        this->position = quadtree::PVector<double>(x, y);
        this->radius = radius;
        this->center_of_mass = center_of_mass;
    }
    Body() {}
};
