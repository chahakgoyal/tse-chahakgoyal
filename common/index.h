/* 
 * index.h
 *
 * Chahak Goyal, Spring 2021
 */
#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"

/************ global types **************/
typedef struct index index_t;


/*********** functions ************/

/********** index_new ***********/
/* creates a new index structure
 * returns null if fails to allocate memory
 * else returns a new index
 */
index_t* index_new (const int num_slots);

/********** index_insert *************/
/* inserts items in index
 * makes a new item every time a key is not present in the index
 */
void index_insert(index_t* index, const char* key, const int id);


/***** index_getItem *******/
void* index_getItem(index_t* index, const char* key);

/*********** index_iterate *************/
// calls hashtable_iterate
void index_iterate(index_t* index, void* arg, void (*hashfunc)(void* arg, const char* key, void* item));

/********** index_save *************/
// calls insert_index and then updates the items
void index_save(index_t* index, const char* key, const int id, const int count);

/*********** index_delete ************/
// deletes the index if it is not null
void index_delete(index_t* index, void(*itemdelete)(void* item));

#endif //__INDEX_H
