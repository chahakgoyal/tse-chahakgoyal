/*
 * set.c - CS50 'set' module
 * 
 * see set.h for more information
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include <string.h>
#include "mem.h"

/****local type****/
typedef struct setnode {
  char* key;
  void *item;
  struct setnode *next;
} setnode_t;

/****global type****/
typedef struct set {
  setnode_t *head;
} set_t;


/****local function****/
/****setnode_new()****/
static setnode_t*
setnode_new(const char* key, void *item) {
  setnode_t* node = mem_malloc(sizeof(setnode_t));

  if (node == NULL) {
    // error allocating memory
    return NULL;
  } else {
    // copy key
    node->key = mem_malloc(strlen(key) + 1);
    if (node->key != NULL) {
      strcpy(node->key, key);
      node->item = item;
      node->next = NULL;
      return node;
    }
  }
  return NULL;
}


/****global function****/
/****set_find()****/
void* set_find(set_t* set, const char* key);

/****set_new()****/
set_t*
set_new(void) {
  set_t* set = mem_malloc(sizeof(set_t));
  if (set == NULL) {
    // error allocating memory to set
    return NULL;
  }
  else {
    // initialize the set
    set->head = NULL;
    return set;
  }
}

/****set_insert()****/
bool set_insert(set_t* set, const char* key, void* item) {
  if (set != NULL && key != NULL && item != NULL) {
    // if key exists in the set
    if (set_find(set, key) != NULL) {
      return false;
    }
    else {
      // make a new node in the set
      setnode_t* new = setnode_new(key, item);
      if (new != NULL) {
        new->next = set->head;
        set->head = new;
      }
    }
    return true;
  }

#ifdef MEMTEST
  mem_report(stdout, "After bag_insert");
#endif
  return false;
}


/****set_find()****/
void* set_find(set_t* set, const char* key) {
  if (set!= NULL && key != NULL) {
    // loop over every node
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
      int i = strcmp(node->key, key);
      // if key exists
      if (i == 0) {
        return node->item;
      }
    }
  }
  return NULL;
}

/****set_print()****/
void set_print(set_t* set, FILE* fp,
               void (*itemprint)(FILE* fp, const char* key, void* item) ) {
  if (fp != NULL) {
    if (set != NULL) {
      fputc('{', fp);
      // loop over every node
      for (setnode_t *node = set->head; node !=NULL; node = node->next) {
        if (itemprint != NULL) {
          // print key and item
          (*itemprint)(fp, node->key, node->item);
          if (node->next != NULL) {
            fputc(',', fp);
          }
        }
      }
      fputc('}', fp);
    } else {
      // print null if set is null
      fputs("(null)", fp);
    }
  }
}

/****set_iterate()****/
void set_iterate(set_t* set, void* arg,
                 void (*itemfunc)(void* arg, const char* key, void* item) ) {
  if (set != NULL && itemfunc != NULL) {
    // loop over every node
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->item);
    }
  }
}

/****set_delete()****/
void set_delete(set_t* set, void (*itemdelete)(void* item) ) {
  if (set != NULL) {
    setnode_t* node = set->head;
    while (node != NULL) {
      if (itemdelete != NULL) {
        //delete node's item
        (*itemdelete)(node->item);
      }
      // remember what comes next
      setnode_t* next = node->next;
      // free the node key
      mem_free(node->key);
      // free the node
      mem_free(node);
      // and move on to next
      node = next;
    }
    mem_free(set);
  }
#ifdef MEMTEST
  mem_report(stdout, "End of set_delete");
#endif
  return;
}
