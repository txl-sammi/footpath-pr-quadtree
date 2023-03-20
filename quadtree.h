#ifndef _QUADTREE_H_
#define _QUADTREE_H_
#include <stdio.h>

// constant definitions
#define QTREE_CAP 4
#define SW 0
#define NW 1
#define NE 2
#define SE 3

// data definitions
typedef struct quadtreeNode quadtreeNode_t;

// prints status of quadtree node
void printStatus(quadtreeNode_t *quad);

// return footpath data from node
footpath_t *getData(quadtreeNode_t *quadtree);

//creates and returns a quadtree node given boundary parameters
quadtreeNode_t *quadtreeCreate(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY);

// inserts points from footpath data into quadtree
void quadtreeInsert(quadtreeNode_t *quadtree, footpath_t *data);

// searches for "query" in quadtree, printing steps taken to reach data point and footpath data
void *quadtreeSearch(quadtreeNode_t *quadtree, point_t *point, FILE *infoFile);

// adds node to "quadtree" children given the direction of the data
void addNode(quadtreeNode_t *quadtree, dataPoint_t *data, int q);

// prints quadrant
void printQuadrant(int q);

// searches for all points in quadtree that are in "rect", printing steps taken to reach data point and footpath data
void *rangeSearch(quadtreeNode_t *quadtree, rectangle_t *rect, FILE *infoFile, array_t *unique);


void searchNode(quadtreeNode_t *quadtree, rectangle_t *rect, FILE *infoFile, array_t *unique, int q);

//frees quad tree
void freeQuadTree(quadtreeNode_t *root);

#endif

