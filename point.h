#include <cstdint>

struct Body {
  public:
    double x;
    double y;
    double radius;

    Body(double x, double y, double radius) {

        this->x = x;
        this->y = y;
        this->radius = radius;
    }
    Body() {}
};
