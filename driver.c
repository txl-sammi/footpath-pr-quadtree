#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "point.h"
#include "data.h"
#include "array.h"
#include "rectangle.h"
#include "quadtree.h"

// used or potential data structures for dictionary
#define STAGE_3 3
#define STAGE_4 4

void rangeQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, char *bottomLeftX, char *bottomLeftY, char *topRightX, char *topRightY);
void quadTreeQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, char *bottomLeftX, char *bottomLeftY, char *topRightX, char *topRightY);
int processArgs(int argc, char *argv[]);

/* driver.c
*
* Created by Sammi Li (tingxin@student.unimelb.edu.au)
09/09/2022
*
* Print the closest footpath data to the user input in stage 3
*
* To run stage 3: 
* ./dict3 --dictionary_type 3 --input_filename dataset.csv --info_file_name output.txt
* To run stage 4:
* ./dict4 --dictionary_type 4 --input_filename dataset.csv --info_file_name output.txt

* To see all the input parameters, type:
* ./dict3 --help or ./dict4 --help
* Options::
*   --help                   Show help message
*   --dictionary_type arg    Input dictionary type
*   --input_file_name arg    Input dataset filename
*   --info_file_name arg     Input output filename  
* 
*/

int main(int argc, char *argv[]) {
	int stageType = processArgs(argc, argv);

    FILE *infoFile = fopen(argv[3], "w");
    assert(infoFile);
    
	switch (stageType) {
		case STAGE_3:
			quadTreeQuerying(argv[2], stdin, stdout, infoFile, argv[4], argv[5], argv[6], argv[7]);
			break;
		case STAGE_4:
			rangeQuerying(argv[2], stdin, stdout, infoFile, argv[4], argv[5], argv[6], argv[7]);
			break;
		default: 
			fprintf(stderr, "Dictionary type %d not yet implemented\n", stageType);
			exit(EXIT_FAILURE);
	}

	fclose(infoFile);
    return 0;
}

// makes sure to have enough arguments in the command line
// returns the specified dictionnary type
int processArgs(int argc, char *argv[]) {
	if (argc < 7 || atoi(argv[1]) < STAGE_3 || atoi(argv[1]) > STAGE_4 ) {
		fprintf(stderr, "Usage: %s dictionary_type input_file_name info_file_name, where:\n", argv[0]);
		fprintf(stderr, "       \t - dictionary_type can be:\n");
		fprintf(stderr, "       \t - input_file_name: data file for buiding dictionary\n");
		fprintf(stderr, "       \t - info_file_name: a file for outputing technical details of searches\n");
		exit(EXIT_FAILURE);
	}
	return atoi(argv[1]);
}

// builds quad tree
quadtreeNode_t *getQuadTree(char *filename, double bottomLeftX, double bottomLeftY, double topRightX, double topRightY){
	FILE *f = fopen(filename, "r");
	assert(f);
	
	// builds starting array
	quadtreeNode_t *quadtree = quadtreeCreate(bottomLeftX, bottomLeftY, topRightX, topRightY);
	footpathSkipHeaderLine(f);
	footpath_t *p;

	while ((p = footpathRead(f))) {
		quadtreeInsert(quadtree, p);
	}
	fclose(f);
	return quadtree;
}

// querying inputs on quadtree 
void quadTreeQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, char *bottomX, char *bottomY, char *topX, char *topY){
	char *ptr;
	double bottomLeftX = strtold(bottomX, &ptr);
	double bottomLeftY = strtold(bottomY, &ptr);
	double topRightX = strtold(topX, &ptr);
	double topRightY = strtold(topY, &ptr);
	
	quadtreeNode_t *quadtree = getQuadTree(dataFileName, bottomLeftX, bottomLeftY, topRightX, topRightY);
	
	char query[MAX_LINE_LEN];
	double x, y;
	while (fgets(query, MAX_LINE_LEN, inFile)!=NULL) {
		int newline = strlen(query)-1;
		if(query[newline] == '\n') {
			query[newline] = '\0';
		}
        fprintf(infoFile, "%s\n", query);
		fprintf(stdout, "%s -->", query);

    	x = strtod(query, &ptr);
		y = strtod(ptr, NULL);

		point_t *point = pointCreate(x, y);

		quadtreeSearch(quadtree, point, infoFile);

		free(point);
	}
	freeQuadTree(quadtree);
}

// creates quadtree from dataset and queries ranges for datapoints that are in the range
void rangeQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, char *bottomX, char *bottomY, char *topX, char *topY){
	char *ptr;
	double bottomLeftX = strtold(bottomX, &ptr);
	double bottomLeftY = strtold(bottomY, &ptr);
	double topRightX = strtold(topX, &ptr);
	double topRightY = strtold(topY, &ptr);
	
	quadtreeNode_t *quadtree = getQuadTree(dataFileName, bottomLeftX, bottomLeftY, topRightX, topRightY);
	
	char query[MAX_LINE_LEN];
	double bottomx, bottomy, topx, topy;
	while (fgets(query, MAX_LINE_LEN, inFile)!=NULL) {
		int newline = strlen(query)-1;
		if(query[newline] == '\n') {
			query[newline] = '\0';
		}
        fprintf(infoFile, "%s\n", query);
		fprintf(stdout, "%s -->", query);

    	bottomx = strtod(query, &ptr);
		bottomy = strtod(ptr, &ptr);
		topx = strtod(ptr, &ptr);
		topy = strtod(ptr, NULL);

		rectangle_t *rect = createRectangle(bottomx, bottomy, topx, topy);
		
		array_t *uniqueFP = arrayCreate();
		rangeSearch(quadtree,rect, infoFile, uniqueFP);
		fprintf(stdout, "\n");

		free(rect);
	}
	freeQuadTree(quadtree);
}
