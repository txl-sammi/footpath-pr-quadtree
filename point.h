#ifndef _POINT_H_
#define _POINT_H_
#include <stdio.h>

// data definitions
typedef struct point point_t;

//creates point from x and y doubles
point_t *pointCreate(double x, double y);

// returns y value
double getY(point_t *point);

// returns x value
double getX(point_t *point);

#endif

