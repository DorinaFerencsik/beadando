#ifndef TEGLA_BRICK_H
#define TEGLA_BRICK_H

typedef struct Brick {
    double x;
    double y;
    double radius;
} Brick;

double setBrickData(Brick* brick, double x, double y, double radius);

/**
 * Calculate the area of the circle.
 */
double getBrickArea(const Brick* brick);

#endif //TEGLA_BRICK_H
