/*
 * index.c
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/mem.h"


/****** struct ******/
typedef struct index {
  hashtable_t* ht;
  counters_t* ctrs;
} index_t;


/******* index_new *******/
index_t* index_new (const int num_slots) {
  index_t* index = mem_malloc(sizeof(index_t));
  if (index == NULL) {
    return NULL;
  }
  index-> ht = hashtable_new(num_slots);
  return index;
}

/******* index_insert *******/
void index_insert(index_t* index, const char* key, const int id) {
  if (hashtable_find(index->ht, key) == NULL && (key != NULL) && (index != NULL)) {
    index->ctrs = counters_new();
    counters_add(index->ctrs, id);
    hashtable_insert(index->ht, key, index->ctrs);
  }
  else {
    index->ctrs = hashtable_find(index->ht, key);
    counters_add(index->ctrs, id);
  }
}

/***** index_getItem *****/
void* index_getItem(index_t* index, const char* key) {
  index->ctrs = hashtable_find(index->ht, key);
  return index->ctrs;
}

/******* index_iterate *******/
void index_iterate(index_t* index, void* arg, void (*hashfunc)(void* arg, const char* key, void* item)) {
  hashtable_iterate(index->ht, arg, hashfunc);
}

/******* index_save ********/
void index_save(index_t* index, const char* key, const int id, const int count) {
  index_insert(index, key, id);
  counters_set(index->ctrs, id, count);
}

/******* index_delete *******/
void index_delete(index_t* index, void(*itemdelete)(void* item)) {
  if (index != NULL) {
    hashtable_delete(index->ht, itemdelete);
    mem_free(index);
  }
}
