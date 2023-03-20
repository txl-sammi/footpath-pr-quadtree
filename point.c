#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "point.h"

// struct for a point
struct point{
    double x;
    double y;
};

//creates a point with x and y values
point_t *pointCreate(double x, double y){
    point_t *point = malloc(sizeof(*point));
    assert(point);
    point->x = x;
    point->y = y;
    return point;
}

//returns x value
double getX(point_t *point) {
    return point->x;
}

//returns y value
double getY(point_t *point) {
    return point->y;
}

