#ifndef _ARRAY_H_
#define _ARRAY_H_

#define INIT_SIZE 2     /* initial size of arrays */

typedef struct array array_t;

// creates & returns an empty array
array_t *arrayCreate();

// free memory used by array "arr"
void arrayFree(array_t *arr);

// makes sure that array's size exceeds its number of elements
//    ie. there is space for adding new element
void arrayEnableInsert(array_t *arr);

// inserts data "p" into sorted array "arr", ensuring "arr" remain sorted 
void sortedArrayInsert(array_t *arr, footpath_t *p);

// checks if footpath "p" is already in array "arr", returns 0 if not, 1 if it is
int checkDuplicates(array_t *arr, footpath_t *p);

void arrayShrink(array_t *arr);

#endif
