#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "point.h"
#include "data.h"
#include "rectangle.h"

//struct for rectangle boundary
struct rectangle {
    double bottomLeftX;
    double bottomLeftY;
    double topRightX;
    double topRightY;
};

// compares two rectangles, returns 1 if there is overlap, 0 if none
int rectcmp(rectangle_t *p, rectangle_t *q) {
    return (pointOverlap(p, q->bottomLeftX, q->bottomLeftY) || pointOverlap(p, q->bottomLeftX, q->topRightY) || pointOverlap(p, q->topRightX, q->bottomLeftY) || pointOverlap(p, q->topRightX, q->topRightY)) || (pointOverlap(q, p->bottomLeftX, p->bottomLeftY) || pointOverlap(q, p->bottomLeftX, p->topRightY) || pointOverlap(q, p->topRightX, p->bottomLeftY) || pointOverlap(q, p->topRightX, p->topRightY));
}

// return bottomleft x coordinate
double getBottomLeftX(rectangle_t *rect){
    return rect->bottomLeftX;
}

// return bottomleft y coordinate
double getBottomLeftY(rectangle_t *rect){
    return rect->bottomLeftY;
}

// return top right x coordinate
double getTopRightX(rectangle_t *rect){
    return rect->topRightX;
}

// return top right y coordinate
double getTopRightY(rectangle_t *rect){
    return rect->topRightY;
}

// return centre x coordinate
double getCentreX(rectangle_t *rectangle){
    return (rectangle->bottomLeftX + rectangle->topRightX)/2;
}

// return centre y coordinate
double getCentreY(rectangle_t *rectangle){
    return (rectangle->bottomLeftY + rectangle->topRightY)/2;
}

// creates rectangle given boundary parameters and returns the rectangle
rectangle_t *createRectangle(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY){
    rectangle_t *rectangle = malloc(sizeof(*rectangle));
    assert(rectangle);
    rectangle->bottomLeftX = bottomLeftX;
    rectangle->bottomLeftY = bottomLeftY;
    rectangle->topRightX = topRightX;
    rectangle->topRightY = topRightY;
    return rectangle;
}

// determines if a point is in a rectangle
int inRectangle(rectangle_t *rectangle, point_t *point){
    return (rectangle->bottomLeftX < getX(point) && rectangle->bottomLeftY < getY(point) && rectangle->topRightX >= getX(point) && rectangle->topRightY >= getY(point));
}

// determines if a point is in a rectangle
int pointOverlap(rectangle_t *rectangle, double x, double y){
    return (rectangle->bottomLeftX < x && rectangle->bottomLeftY < y && rectangle->topRightX >= x && rectangle->topRightY >= y);
}

// determines which quadrant a point lies on a rectangle
int compass(rectangle_t *rectangle, point_t *point){
    double centreX = (rectangle->bottomLeftX + rectangle->topRightX)/2;
    double centreY = (rectangle->bottomLeftY + rectangle->topRightY)/2;
    // south west = 0
    if (getX(point) <= centreX && getY(point) < centreY){
        return 0;
    }
    // north west = 1
    if (getX(point) <= centreX && getY(point) >= centreY){
        return 1;
    }
    // north east = 2
    if (getX(point) > centreX && getY(point) >= centreY){
        return 2;
    }
    // south east = 3
    if (getX(point) > centreX && getY(point) < centreY){
        return 3;
    }
}
