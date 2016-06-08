#ifndef Train_UTILITIES_H
#define Train_UTILITIES_H
#include <stdio.h>

/******************************************************************************
 * This file contains general utilities for handling Person type - copying,
 * comparing, freeing, printing and matching by different keys.
 * These utilites can be used for defining generic ADTs to hold elements
 * of the Person type
 *****************************************************************************/
void* copy_train(void* elm);
void free_train(void* elm); 
void print_train(FILE* outstream,void* elm); 
int compare_train_type(void* elm1, void* elm2); 
/* compares by type then line */
int compare_train_price(void* elm1, void* elm2);
int match_by_line_number_train(void* elm, void* key);


#endif /* Train_UTILITIES_H */
