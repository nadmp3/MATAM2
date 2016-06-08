#ifndef Station_UTILITIES_H
#define Station_UTILITIES_H
#include <stdio.h>

/******************************************************************************
 * This file contains general utilities for handling Person type - copying,
 * comparing, freeing, printing and matching by different keys.
 * These utilites can be used for defining generic ADTs to hold elements
 * of the Station type
 *****************************************************************************/
void* copy_station(void* elm);
void free_station(void* elm); 
void print_station(FILE* outstream,void* elm); 
int compare_station(void* elm1, void* elm2); //return 0 when the are the same
/* compares by station name */
int match_by_Station_name(void* elm, void* key);//return 1 when key=elm

#endif /* Station_UTILITIES_H */
