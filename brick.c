#include "brick.h"

#include "math.h"

double setBrickData(Brick* brick, double x, double y, double radius){
    brick->x = x;
    brick->y = y;
    if(radius > 0.0){
        brick->radius = radius;
    } else {
        brick->radius = NAN;
    }
}

double getBrickArea(const Brick* brick){
    double area = brick->radius * brick->radius * M_PI;
    return area;
}