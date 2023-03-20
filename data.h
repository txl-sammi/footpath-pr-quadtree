#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>

//constant definitions
#define MAX_STRING_LEN 128     /* max length of a string */
#define MAX_LINE_LEN 512       /* max length of a line */
#define MAX_INPUTS 19          /* max number of data inputs */

// data definitions
typedef struct footpath footpath_t;
typedef struct dataPoint dataPoint_t;

/*------------ function definitions -----------------------------*/

// skip the header line of .csv file "f"
void footpathSkipHeaderLine(FILE *f);

// reads a footpath from file "f" to build a footpath_t data
// returns the pointer, or NULL if reading is unsuccessful
footpath_t *footpathRead(FILE *f);

// prints a footpath record *p to file "f"
void footpathPrint(FILE *f, footpath_t *p);

// free the memory allocated to a footpath "p"
void footpathFree(void *p);

// return address of footpath "p"
char *getFootpathAddress(void *p);

// compares the address of footpath "p" and returns 0 if they are equal
int addresscmp(char *query, footpath_t *p);

// compares the grade1in of footpath "f" and footpath "p"
//    returns 0 if equal, -1 if f is less than p, 1 if f is greater than p
int grade1incmp(footpath_t *f, footpath_t *p);

// returns the absolute difference between grade1in of footpath "f" and "query"
double getDifference(footpath_t *f, double query);

// returns grade1in of footpath "f"
double getGrade1in(footpath_t *f);

// returns start_lat of footpath "f"
double getStartLat(footpath_t *f);

// returns start_lon of footpath "f"
double getStartLon(footpath_t *f);

// returns end_lat of footpath "f"
double getEndLat(footpath_t *f);

// returns start_lon of footpath "f"
double getEndLon(footpath_t *f);

// creates data point for the end point of the footpath
dataPoint_t *createDataPointEnd(footpath_t *data);

// creates data point for the start point of the footpath
dataPoint_t *createDataPointStart(footpath_t *data);

// returns footpath from a data point
footpath_t *getFootpath(dataPoint_t *dataP);

//returns a point from a data point
point_t *getPoint(dataPoint_t *dataP);

//frees data point
void freeDataP(dataPoint_t *dataP);

// compares the id of footpath "f" and footpath "p"
//    returns 0 if equal, -1 if f is less than p, 1 if f is greater than p
int footpathcmp(footpath_t *f, footpath_t *p);

#endif

