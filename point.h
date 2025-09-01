#include <cstdint>

struct Body {
    public:
        double x;
        double y;
        double radius ;
        double center_of_mass;

    Body(double x , double y , double radius, double center_of_mass){
        this->x = x;
        this->y = y;
        this->radius = radius;
        this->center_of_mass = center_of_mass;
    }
    Body(){

    }
    

};

