#ifndef Track_UTILITIES_H
#define Track_UTILITIES_H
#include <stdio.h>

/******************************************************************************
 * This file contains general utilities for handling Person type - copying,
 * comparing, freeing, printing and matching by different keys.
 * These utilites can be used for defining generic ADTs to hold elements
 * of the Person type
 *****************************************************************************/
void* copy_track(void* elm);
void free_track(void* elm); 
void print_track(FILE* outstream,void* elm); 
int compare_track(void* elm1, void* elm2); 
/* compares by station */
int match_by_time_from_first(void* elm, void* key);

#endif /* Track_UTILITIES_H */
