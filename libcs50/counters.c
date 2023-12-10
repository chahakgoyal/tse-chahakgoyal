/*
 * counters.c - CS50 'counters' module
 * 
 * see counters.h for more information
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "counters.h"
#include <string.h>
#include "mem.h"

/****local type****/
typedef struct countersnode {
  int key;
  int counter;
  struct countersnode *next;
} countersnode_t;

/****global type****/
typedef struct counters {
  countersnode_t *head;
} counters_t;


/****local function****/
static countersnode_t*
countersnode_new(const int key, int counter) {
  countersnode_t* node = mem_malloc(sizeof(countersnode_t));

  if (node == NULL) {
    // error allocating memory
    return NULL;
  } else {
    node->key = key;
    node->counter = counter;
    node->next = NULL;
    return node;
  }
  return NULL;
}

/****global functions****/

/****counters_new()****/
counters_t*
counters_new(void) {
  counters_t* counters = mem_malloc(sizeof(counters_t));
  if (counters == NULL) {
    // error allocating memory
    return NULL;
  }
  else {
    counters->head = NULL;
    return counters;
  }
}

/****counters_add()****/
int counters_add(counters_t* ctrs, const int key) {
  if (ctrs != NULL && key >= 0) {
    // if node already exists then increment item value
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key) {
        node ->counter++;
        return node->counter;
      }
    }
    // else create a new node
    countersnode_t* new = countersnode_new(key, 1);
    if (new != NULL) {
      new->next = ctrs->head;
      ctrs->head = new;
      return new->counter;
    }
  }

#ifdef MEMTEST
  mem_report(stdout, "After counters_add");
#endif
  return 0;
}

/****counters_get()****/
int counters_get(counters_t* ctrs, const int key) {
  if (ctrs!= NULL && key >= 0) {
    // see if key exists and return item if it does
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key) {
        return node->counter;
      }
    }
  }
  return 0;
}

/****counters_set****/
bool counters_set(counters_t* ctrs, const int key, const int count) {
  if (ctrs != NULL && key >= 0 && count >= 0) {
    // if node exists then update its value 
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key) {
        node->counter = count;
        return true;
      }
    }
    // otherwise create a new node
    countersnode_t *new = countersnode_new(key, 1);
    if (new != NULL) {
      new->next = ctrs->head;
      ctrs->head = new;
    }
    return true;
  }
  return false;
}


/****counters_print()****/
void counters_print(counters_t* ctrs, FILE* fp) {
  if (fp != NULL) {
    if (ctrs != NULL) {
      fputc('{', fp);
      for (countersnode_t *node = ctrs->head; node !=NULL; node = node->next) {
        fprintf(fp, "%d=%d", node->key, node->counter);
        if (node->next != NULL) {
          fprintf(fp, ",");
        }
      }
      fputc('}', fp);
    } else {
      // if counters is null
      fputs("(null)", fp);
    }
  }
}

/****counters_iterate()****/
void counters_iterate(counters_t* ctrs, void* arg,
                      void (*itemfunc)(void* arg,
                                       const int key, const int count)) {
  if (ctrs != NULL && itemfunc != NULL) {
    for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->counter);
    }
  }
}

/****counters_delete()****/
void counters_delete(counters_t *ctrs) {
  if (ctrs != NULL) {
    countersnode_t* node = ctrs->head;
    while (node != NULL) {
      // remember what comes next
      countersnode_t* next = node->next;
      // free the node
      mem_free(node);
      // go to the next node
      node = next;
    }
    mem_free(ctrs);
  }
#ifdef MEMTEST
  mem_report(stdout, "End of counters_delete");
#endif
  return;
}
