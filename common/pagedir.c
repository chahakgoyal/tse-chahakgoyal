/*
 * pagedir.c
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/mem.h"
#include "../libcs50/webpage.h"
#include "index.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include <string.h>
#include "../libcs50/file.h"

/********* local functions **********/
static void hashfunc(void* arg, const char* key, void* item);
static void itemfunc(void* arg, const int id, const int count);
static void delete_func(void* item);


/********* global functions *********/
/****pagedir_init****/
bool pagedir_init(const char* pageDirectory) {
  // create filename
  char* filename = malloc(50*sizeof(filename));
  sprintf(filename, "%s/.crawler", pageDirectory);
  FILE *fp;
  // if can be opened for writing then return true else return false
  fp = fopen(filename, "w");
  if (fp == NULL) {
    return false;
  }
  // close the file and free the filename
  fclose(fp);
  free(filename);
  return true;
}

/****pagedir_save****/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {
  // create filename
  char* file =  malloc(strlen(pageDirectory) + 11);
  sprintf(file, "%s/%d", pageDirectory, docID);
  FILE *fp;
  // if can create file then save the page otherwise exit with non-zero status
  fp = fopen(file, "w");
  if (fp == NULL) {
    fprintf(stderr, "Unable to create file\n");
    exit(2);
  }
  fprintf(fp, "%s\n", webpage_getURL(page));
  fprintf(fp, "%d\n", webpage_getDepth(page));
  webpage_t* wbpg = (webpage_t*) page;
  fprintf(fp, "%s", webpage_getHTML(wbpg));
  // close the file and free the filename
  fclose(fp);
  free(file);
}

/***** pagedir_validate *****/
// validates the directory
bool pagedir_validate(const char* pageDirectory) {
  FILE* fp;
  bool exists = false;
  // pageDirectory/.crawler
  char* filename = malloc(50*sizeof(filename));
  sprintf(filename, "%s/.crawler", pageDirectory);
  // check if file exists
  fp = fopen(filename, "r");
  if (fp != NULL) {
     exists = true;
  }
  else {
    return exists;
  }
  fclose(fp);
  free(filename);
  return exists;
}


/******* pagedir_load *******/
// load the webpage by reading URL and depth from the associated file
// returns the webpage
webpage_t* pagedir_load(const char* pageDirectory, const int docId) {
  FILE* fp;
  char* filename = malloc(strlen(pageDirectory) + 11);
  sprintf(filename, "%s/%d", pageDirectory, docId);
  fp = fopen(filename, "r");
  // if file cannot be opened to read return NULL
  if (fp == NULL) {
    free(filename);
    return NULL;
  }
  char* URL;
  char* depth;
  int i = 0;
  while (i < 2) {
    if (i == 0) {
      URL = file_readLine(fp);
    } else if (i == 1) {
      depth = file_readLine(fp);
    }
    i++;
  }
  int d = atoi(depth);
  webpage_t* webpage = webpage_new(normalizeURL(URL), d, NULL);
  fclose(fp);
  free(depth);
  free(URL);
  free(filename);
  return webpage;
}

/******* pagedir_delete *******/
// function to delete the index
void pagedir_delete(index_t* index) {
  index_delete(index, delete_func);
}

/***** local function - delete_func *****/
// local function called in index delete to delete index's counters
static void delete_func(void* item) {
  counters_t* counters = item;
  counters_delete(counters);
}

/******* pagedir_write ********/
// prints the index to the given file by calling index_iterate
void pagedir_write(index_t* index, FILE* fp) {
  index_iterate(index, fp, hashfunc);
}

/********* local function - hashfunc **********/
// local function called in index_iterate to iterate over index's counters and print words
static void hashfunc(void* arg, const char* key, void* item) {
  FILE *fp = arg;
  counters_t *counters = (counters_t*) item;
  if (fp != NULL && key != NULL && item != NULL) {
    fprintf(fp, "%s ", key);
    counters_iterate(counters, fp, itemfunc);
    fprintf(fp, "\n");
  }
}

/******* local function - itemfunc *******/
// local function called in counters_iterate to print id and count
static void itemfunc(void* arg, const int id, const int count) {
  FILE* fp = arg;
  if (id >= 0) {
    fprintf(fp, "%d %d ", id, count);
  }
}
