#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include <stdio.h>

// data definitions
typedef struct rectangle rectangle_t;

// creates rectangle given boundary parameters and returns the rectangle
rectangle_t *createRectangle(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY);

// determines if a point is in a rectangle
int inRectangle(rectangle_t *rectangle, point_t *point);

// determines if pair of coorindates overlap with rectangle
int pointOverlap(rectangle_t *rectangle, double x, double y);

// compares two rectangles, returns 1 if there is overlap, 0 if none
int rectcmp(rectangle_t *p, rectangle_t *q);

// determines which quadrant a point lies on a rectangle
int compass(rectangle_t *rectangle, point_t *point);

// return bottomleft x coordinate
double getBottomLeftX(rectangle_t *rect);

// return bottomleft y coordinate
double getBottomLeftY(rectangle_t *rect);

// return top right x coordinate
double getTopRightX(rectangle_t *rect);

// return top right y coordinate
double getTopRightY(rectangle_t *rect);

// return centre x coordinate
double getCentreX(rectangle_t *rectangle);

// return centre y coordinate
double getCentreY(rectangle_t *rectangle);

#endif

