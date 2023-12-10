/*
 * hashtable module - see hashtable.h for more information
 *
 * Chahak Goyal, Spring 2021
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mem.h"
#include "hashtable.h"
#include "set.h"
#include "hash.h"

/****global type****/
typedef struct hashtable {
  int num;
  set_t** array;
} hashtable_t;


/****global functions****/
/****hashtable_new()****/
hashtable_t* hashtable_new(const int num_slots) {
  hashtable_t* hashtable = mem_malloc(sizeof(hashtable_t));
  if (hashtable == NULL) {
    // error allocating memory
    return NULL;
  }
  if (num_slots > 0) {
    hashtable->num = num_slots;
    hashtable->array = calloc(hashtable->num, sizeof(set_t*));
    // for every slot make new set
    for (int i = 0; i < num_slots; i++) {
      hashtable->array[i] = set_new();
    }
  }
  return hashtable;
}

/****hashtable_insert()****/
bool hashtable_insert(hashtable_t* ht, const char* key, void* item) {
  if (ht != NULL && key != NULL && item != NULL) {
    int i = hash_jenkins(key, ht->num);
    return set_insert(ht->array[i], key, item);
  } 
  return false;
}


/****hashtable_find()****/
void* hashtable_find(hashtable_t* ht, const char* key) {
  if (ht != NULL && key != NULL) {
    int i = hash_jenkins(key, ht->num);
    // if key exists in the specific slot set return the value
    if (set_find(ht->array[i], key) != NULL) {
      return set_find(ht->array[i], key);
    }
  }
  return NULL;
}

/****hashtable_print()****/
void hashtable_print(hashtable_t* ht, FILE* fp,
                     void (*itemprint)(FILE* fp, const char* key, void* item)) {
  if (fp != NULL) {
    if (ht != NULL) {
      fputc('{', fp);
      fputs("\n", fp);
      if (itemprint != NULL) {
        // call set_print() for every slot
        for (int i = 0; i < ht->num; i++) {
          set_print(ht->array[i], fp, itemprint);
          fputs("\n", fp);
        }
      } else {
        for (int i = 0; i < ht->num; i++) {
          fputs("\n", fp);
        }
      }
      fputc('}', fp);
    } else {
      fputs("(null)", fp);
    }
  }
}

/****hashtable_iterate()****/
void hashtable_iterate(hashtable_t* ht, void* arg,
                       void (*itemfunc)(void* arg, const char* key, void* item)) {
  if (ht != NULL && itemfunc != NULL) {
    // call set_iterate for every slot
    for (int i = 0; i < ht->num; i++) {
      set_iterate(ht->array[i], arg, itemfunc);
    }
  }
}

/****hashtable_delete()****/
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ) {
  if (ht != NULL) {
    // call set_delete() for every slot
    for (int i = 0; i < ht->num; i++) {
      set_delete(ht->array[i], itemdelete);
    }
    mem_free(ht->array);
    mem_free(ht);
  }
}
