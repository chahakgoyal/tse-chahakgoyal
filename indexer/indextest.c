/*
 * indextest.c
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "../common/index.h"
#include "../libcs50/file.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include <string.h>
#include "../common/pagedir.h"

static void loadIndex(char* oldIndexFilename, char* newIndexFilename);
static void index_print(index_t* index, char* newIndexFilename);
int main(const int argc, char* argv[]);

/*********** loadIndex ************/
/* reads from the old index file
 * and loads it into a new index
 * calls index_print on the index
 */
static void loadIndex(char* oldIndexFilename, char* newIndexFilename) {
  FILE *fp;
  fp = fopen(oldIndexFilename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Unable to read file");
    exit(1);
  }
  // size of index = num of words = num of lines in old index file
  index_t* index = index_new(file_numLines(fp));
  char* word;
  while ((word = file_readWord(fp)) != NULL) {
    int id;
    int count;
    // getting the id, count pairs
    while (fscanf(fp, "%d %d", &id, &count) == 2) {
      index_save(index, word, id, count);
    }
    free(word);
  }
  fclose(fp);
  index_print(index, newIndexFilename);
  pagedir_delete(index);
}


/********* index_print *********/
// prints out the new index
void index_print(index_t* index, char* newIndexFilename) {
  FILE* fp;
  fp = fopen(newIndexFilename, "w");
  if (fp == NULL) {
    fprintf(stderr, "Unable to write file");
    exit(2);
  }
  pagedir_write(index, fp);
  fclose(fp);
}


/***** main *****/
// calls loadIndex
int main (const int argc, char* argv[]) {
  if (argc == 3) {
    loadIndex(argv[1], argv[2]);
    return 0;
  }
  fprintf(stderr, "Incorrect number of arguments");
  exit(2);
}
  
