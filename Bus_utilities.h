#ifndef PERSON_UTILITIES_H
#define PERSON_UTILITIES_H
#include <stdio.h>

/******************************************************************************
 * This file contains general utilities for handling Person type - copying,
 * comparing, freeing, printing and matching by different keys.
 * These utilites can be used for defining generic ADTs to hold elements
 * of the Person type
 *****************************************************************************/
void* copy_bus(void* elm);
void free_bus(void* elm); 
void print_bus(FILE* outstream,void* elm); 
int compare_bus_company_name(void* elm1, void* elm2); 
/* compares by first name, last name and id */
int compare_bus_price(void* elm1, void* elm2);
int match_by_line_bus(void* elm, void* key);
int match_by_price_bus(void* elm, void* key);

#endif /* PERSON_UTILITIES_H */
