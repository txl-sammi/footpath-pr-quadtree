#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "point.h"
#include "data.h"
#include "array.h"
#include "rectangle.h"
#include "quadtree.h"


//struct for quadtree
struct quadtreeNode {
    int numNodes;
    rectangle_t *rectangle;
    quadtreeNode_t *children[QTREE_CAP];
    dataPoint_t *dataPoint;
};

//creates and returns a quadtree node given boundary parameters
quadtreeNode_t *quadtreeCreate(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY) {
    quadtreeNode_t *quadtree = malloc(sizeof(*quadtree));
    assert(quadtree);
    quadtree->numNodes = 0;
    quadtree->dataPoint == NULL;
    quadtree->rectangle = createRectangle(bottomLeftX, bottomLeftY, topRightX, topRightY);
    quadtree->children[SW] = quadtree->children[NW] = quadtree->children[NE] = quadtree->children[SE] = NULL;
    return quadtree;
}

// return footpath data from node
footpath_t *getData(quadtreeNode_t *quadtree){
    return getFootpath(quadtree->dataPoint);
}

// adds node to "quadtree" children given the direction of the data
void addNode(quadtreeNode_t *quadtree, dataPoint_t *data, int q){
    q = compass(quadtree->rectangle, getPoint(data));
    if (quadtree->children[q] == NULL){
        if (q == SW) {
	        quadtreeNode_t *newNode = quadtreeCreate(getBottomLeftX(quadtree->rectangle), getBottomLeftY(quadtree->rectangle), getCentreX(quadtree->rectangle), getCentreY(quadtree->rectangle));
            assert(newNode);
            newNode->dataPoint = data;
            quadtree->children[q] = newNode;
            (quadtree->numNodes)++;
        }
        if (q == NW) {
            quadtreeNode_t *newNode = quadtreeCreate(getBottomLeftX(quadtree->rectangle), getCentreY(quadtree->rectangle), getCentreX(quadtree->rectangle), getTopRightY(quadtree->rectangle));
    	    assert(newNode);
            newNode->dataPoint = data;
            quadtree->children[q] = newNode;
            (quadtree->numNodes)++;
        }
        if (q == NE) {
	        quadtreeNode_t *newNode = quadtreeCreate(getCentreX(quadtree->rectangle), getCentreY(quadtree->rectangle), getTopRightX(quadtree->rectangle), getTopRightY(quadtree->rectangle));
            assert(newNode);
            newNode->dataPoint = data;
            quadtree->children[q] = newNode;
            (quadtree->numNodes)++;
        }
        if (q == SE) {
	        quadtreeNode_t *newNode = quadtreeCreate(getCentreX(quadtree->rectangle), getBottomLeftY(quadtree->rectangle), getTopRightX(quadtree->rectangle), getCentreY(quadtree->rectangle));
            assert(newNode);
            newNode->dataPoint = data;
            quadtree->children[q] = newNode;
            (quadtree->numNodes)++;
        }
    }
    else {
        addNode(quadtree->children[q], quadtree->children[q]->dataPoint, q);
        addNode(quadtree->children[q], data, q);
    }
}

// inserts points from footpath data into quadtree
void quadtreeInsert(quadtreeNode_t *quadtree, footpath_t *data){
    assert(quadtree);

    dataPoint_t *dataPStart = createDataPointStart(data);
    int q = compass(quadtree->rectangle, getPoint(dataPStart));
    addNode(quadtree, dataPStart, q);

    dataPoint_t *dataPEnd = createDataPointEnd(data);
    int p = compass(quadtree->rectangle, getPoint(dataPEnd));
    addNode(quadtree, dataPEnd, p);
}

// prints quadrant
void printQuadrant(int q){
    if (q == SW) {
        fprintf(stdout, " SW");
    }
    if (q == NW) {
        fprintf(stdout, " NW");
    }
    if (q == NE) {
        fprintf(stdout, " NE");
    }
    if (q == SE) {
        fprintf(stdout, " SE");
    }
}

// searches for "query" in quadtree, printing steps taken to reach data point and footpath data
void *quadtreeSearch(quadtreeNode_t *quadtree, point_t *point, FILE *infoFile) {
    
    int q = compass(quadtree->rectangle, point);
    
    if(quadtree->children[q] != NULL) {
        printQuadrant(q);
        quadtreeSearch(quadtree->children[q], point, infoFile);
    } 
    else {
        footpathPrint(infoFile, getData(quadtree));
        fprintf(stdout, "\n");
    }
}

// searches for all points in quadtree that are in "rect", printing steps taken to reach data point and footpath data
void *rangeSearch(quadtreeNode_t *quadtree, rectangle_t *rect, FILE *infoFile, array_t *unique) {
    if (quadtree->children[SW] != NULL) {
        searchNode(quadtree, rect, infoFile, unique, SW);
    }
    if (quadtree->children[NW] != NULL) {
        searchNode(quadtree, rect, infoFile, unique, NW);
    }
    if (quadtree->children[NE] != NULL) {
        searchNode(quadtree, rect, infoFile, unique, NE);
    }
    if (quadtree->children[SE] != NULL) {
        searchNode(quadtree, rect, infoFile, unique, SE);
    }
}

void searchNode(quadtreeNode_t *quadtree, rectangle_t *rect, FILE *infoFile, array_t *unique, int q) {
    if (rectcmp(quadtree->children[q]->rectangle, rect) == 1) {
        printQuadrant(q);
        if (quadtree->children[q] != NULL) {
            if (inRectangle(rect, getPoint(quadtree->children[q]->dataPoint))) {
                if (checkDuplicates(unique, getFootpath(quadtree->children[q]->dataPoint)) == 0) {
                    sortedArrayInsert(unique, getFootpath(quadtree->children[q]->dataPoint));
                    footpathPrint(infoFile, getData(quadtree->children[q]));
                }
            }
        
            rangeSearch(quadtree->children[q], rect, infoFile, unique);
        }
    }
}

// prints status of quadtree node
void printStatus(quadtreeNode_t *quad){
    if (quad->dataPoint != NULL) {
        printf("NODE FILLED\n");
    }
    if (quad->children[SW] != NULL){
        printf("SW FILLED\n");
    } else {
        printf("SW EMPTY\n");
    }
    if (quad->children[NW] != NULL){
        printf("NW FILLED\n");
    } else {
        printf("NW EMPTY\n");
    }
    if (quad->children[NE] != NULL){
        printf("NE FILLED\n");
    } else {
        printf("NE EMPTY\n");
    }
    if (quad->children[SE] != NULL){
        printf("SE FILLED\n");
    } else {
        printf("SE EMPTY\n");
    }
}

//frees quad tree
void freeQuadTree(quadtreeNode_t *root) {
    
    free(root->rectangle);
    if (root->children[SW] != NULL) {
        freeQuadTree(root->children[SW]);
    }
    if (root->children[NW] != NULL) {
        freeQuadTree(root->children[NW]);
    }
    if (root->children[NE] != NULL) {
        freeQuadTree(root->children[NE]);
    }
    if (root->children[SE] != NULL) {
        freeQuadTree(root->children[SE]);
    }
    if (root->dataPoint != NULL) {
    }

    free(root);
}
