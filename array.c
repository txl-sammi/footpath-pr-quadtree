#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "point.h"
#include "data.h"
#include "array.h"

struct array {
	footpath_t **A;      // use as array of footpath_t *
	int size;           // current array size
	int n;              // current number of elements
};

// creates & returns an empty array
array_t *arrayCreate() {
	array_t *arr = malloc(sizeof(*arr));
	assert(arr);
	int size = INIT_SIZE;
	arr->size = size;
	arr->A = malloc(size * sizeof(*(arr->A)));
	assert(arr->A);
	arr->n = 0;
	return arr;
}

// free memory used by array "arr"
void arrayFree(array_t *arr) {
	for (int i = 0; i < arr->n; i++) {
		footpathFree(arr->A[i]);
	}
	free(arr->A);
	free(arr);
}

// makes sure that array's size exceeds its number of elements
//    ie. there is space for adding new element
void arrayEnableInsert(array_t *arr) {
	if (arr->n == arr->size) {
		arr->size <<= 1;       // same as arr->size *= 2;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}

// inserts data "p" into array "arr"
void sortedArrayInsert(array_t *arr, footpath_t *p) {
	int i;
	arrayEnableInsert(arr);
	// starting from the end, shift all elements > p one position to the right

	for (i = arr->n - 1; i >= 0 && footpathcmp(p, arr->A[i]) == -1 ; i-- ) {
		arr->A[i + 1] = arr->A[i];
	}
	// now "p" should be in A[i + 1]
	arr->A[i + 1] = p;
	arr->n++;
	
}


// shrinks the array, to reduce array size to the same 
//    as the number of element used
void arrayShrink(array_t *arr) {
	if (arr->size != arr->n) {
		// the new size should be at least INIT_SIZE
		arr->size = (arr->n > INIT_SIZE) ? arr->n : INIT_SIZE;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}


// checks if footpath "p" is already in array "arr", returns 0 if not, 1 if it is
int checkDuplicates(array_t *arr, footpath_t *p) {
	int i;
	for (i = arr->n - 1; i >= 0 && footpathcmp(p, arr->A[i]) == 0 ; i-- ) {
		return 1;
	}
	return 0;
}
