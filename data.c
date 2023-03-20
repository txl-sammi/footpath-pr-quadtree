#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "point.h"
#include "data.h"

// struct for footpath data
struct footpath {
	int footpath_id;
	char *address;
	char *clue_sa;
	char *asset_type;
	double deltaz;
	double distance;
	double grade1in;
	int mcc_id;
	int mccid_int;
	double rlmax;
	double rlmin;
	char *segside;
	int statusid;
	int streetid;
	int street_group;
	double start_lat;
	double start_lon;
	double end_lat;
	double end_lon;
};

// struct for data point
struct dataPoint {
	footpath_t *data;
	point_t *point;
};

// returns a data point of the end point of the footpath
dataPoint_t *createDataPointEnd(footpath_t *data){
	dataPoint_t *datapoint = malloc(sizeof(*datapoint));
	assert(datapoint);
	datapoint->data = data;
	datapoint->point = pointCreate(data->end_lon, data->end_lat);

	return datapoint;
}

// returns a data point of the start point of the footpath
dataPoint_t *createDataPointStart(footpath_t *data){
	dataPoint_t *datapoint = malloc(sizeof(*datapoint));
	assert(datapoint);
	datapoint->data = data;
	datapoint->point = pointCreate(data->start_lon, data->start_lat);

	return datapoint;
}

// frees data point
void freeDataP(dataPoint_t *dataP) {
	if (dataP->data != NULL){
		footpathFree(dataP->data);
	}
	if (dataP->point != NULL) {
		free(dataP->point);
	}
}

// returns footpath data from data point
footpath_t *getFootpath(dataPoint_t *dataP) {
	return dataP->data;
}

//returns point from data point
point_t *getPoint(dataPoint_t *dataP) {
	return dataP->point;
}

// skip the header line of .csv file "f"
void footpathSkipHeaderLine(FILE *f) {
	while (fgetc(f) != '\n');
}

// reads a footpath from file "f" to build a footpath_t data.
// returns the pointer, or NULL if reading is unsuccessful.
footpath_t *footpathRead(FILE *f) {
	footpath_t *p = NULL;
	char inputs[MAX_INPUTS][MAX_STRING_LEN];
	char line[MAX_LINE_LEN];
	int quote=0, i, input=0, index=0;

	for (i=0; i<MAX_INPUTS; i++) {
		memset(inputs[i], 0, sizeof(inputs[i]));
	}
	
	// reads one line and iterates through the characters
	//    to ensure empty entries and '"' are read properly
	if (fgets(line, MAX_LINE_LEN, f) != NULL) {
		p = malloc(sizeof(*p));
		assert(p);
		
		for (i=0; i<strlen(line); i++) {
			if (line[i] == '"') {
				if (quote == 1) {
					quote = 0;
				} 
				else {
					quote = 1;
				}
			}
			if (line[i] != ',' && line[i] != '"') {
				inputs[input][index] = line[i];
				index++;
			} 
			else if (line[i] == ',') {
				if (quote != 1) {
					input++;
					index=0;
				} else {
					inputs[input][index] = line[i];
					index++;
				}
			}
		}
		p->footpath_id = atoi(inputs[0]);
		p->address = strdup(inputs[1]);
		assert(p->address);
		p->clue_sa = strdup(inputs[2]);
		assert(p->clue_sa);
		p->asset_type = strdup(inputs[3]);
		assert(p->asset_type);
		p->deltaz = atof(inputs[4]);
		p->distance = atof(inputs[5]);
		p->grade1in = atof(inputs[6]);
		p->mcc_id = atoi(inputs[7]);
		p->mccid_int = atoi(inputs[8]);
		p->rlmax = atof(inputs[9]);
		p->rlmin = atof(inputs[10]);
		p->segside = strdup(inputs[11]);
		assert(p->segside);
		p->statusid = atoi(inputs[12]);
		p->streetid = atoi(inputs[13]);
		p->street_group = atoi(inputs[14]); 
		p->start_lat = atof(inputs[15]);
		p->start_lon = atof(inputs[16]);
		p->end_lat = atof(inputs[17]);
		p->end_lon = atof(inputs[18]);
	}
	
	return p;
}

// prints a footpath record *p to file "f"
void footpathPrint(FILE *f, footpath_t *p) {
	fprintf(f, "--> footpath_id: %d || address: %s || clue_sa: %s || asset_type: %s || deltaz: %.2lf || distance: %.2lf || grade1in: %.1lf || mcc_id: %d || mccid_int: %d || rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d || streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf || end_lat: %.6lf || end_lon: %.6lf || \n",
			p->footpath_id, p->address, p->clue_sa, p->asset_type, p->deltaz, p->distance, p->grade1in, p->mcc_id, p->mccid_int, p->rlmax, p->rlmin, p->segside, p->statusid, p->streetid, p->street_group, p->start_lat, p->start_lon, p->end_lat, p->end_lon);
} 

// free the memory allocated to a footpath "p"
void footpathFree(void *p) {
	free(((footpath_t *)p)->address);
	free(((footpath_t *)p)->clue_sa);
	free(((footpath_t *)p)->asset_type);
	free(((footpath_t *)p)->segside);
	free(p);
}

// return address of footpath "p"
char *getFootpathAddress(void *p) {
	return ((footpath_t *)p)->address;
}

// compares the address of footpath "p" and returns 0 if they are equal
int addresscmp(char *query, footpath_t *p) {
	return strcmp(query, p->address);
}

// compares the grade1in of footpath "f" and footpath "p"
//    returns 0 if equal, -1 if f is less than p, 1 if f is greater than p
int grade1incmp(footpath_t *f, footpath_t *p) {
	if (f->grade1in > p->grade1in) {
		return 1;
	}
	if (f->grade1in < p->grade1in) {
		return -1;
	}
	if (f->grade1in == p->grade1in) {
		return 0;
	}
}

// compares the id of footpath "f" and footpath "p"
//    returns 0 if equal, -1 if f is less than p, 1 if f is greater than p
int footpathcmp(footpath_t *f, footpath_t *p) {
	if (f->footpath_id > p->footpath_id) {
		return 1;
	}
	if (f->footpath_id < p->footpath_id) {
		return -1;
	}
	if (f->footpath_id == p->footpath_id) {
		return 0;
	}
}

// returns the absolute difference between grade1in of footpath "f" and "query"
double getDifference(footpath_t *f, double query) {
	return fabs((f->grade1in) - query);
}

// returns grade1in of footpath "f"
double getGrade1in(footpath_t *f) {
	return (f->grade1in);
}

// returns start_lat of footpath "f"
double getStartLat(footpath_t *f) {
	return (f->start_lat);
}

// return start_lon of footpath "f"
double getStartLon(footpath_t *f) {
	return (f->start_lon);
}

// return end_lat of footpath "f"
double getEndLat(footpath_t *f) {
	return (f->end_lat);
}

// return end_lon of footpath "f"
double getEndLon(footpath_t *f) {
	return (f->end_lon);
}

