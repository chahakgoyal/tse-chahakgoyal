/*
 * indexer.c
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../libcs50/mem.h"
#include "../libcs50/file.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../common/index.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../common/word.h"



/*********** function definitions *************/
static void parseArgs(const int argc, char* argv[], char* pageDirectory, char* indexFilename);
static void indexBuild(char* pageDirectory, char* indexFile);
static void indexPage(index_t* index, webpage_t* load, int docID);
int main(const int argc, char* argv[]);



/****** parseArgs ******/
/* parses the arguments
 * validates the directory given
 */
static void parseArgs(const int argc, char* argv[], char* pageDirectory, char* indexFilename) {
  if (argc == 3) {
    if (pagedir_validate(pageDirectory) == true) {
      return;
    }
    else {
      fprintf(stderr, "Unable to validate directory.\n");
      exit(2);
    }
  }
  else {
    fprintf(stderr, "Invalid number of arguments\n");
    exit(2);
  }
}


/********** indexBuild ***********/
/* builds the index
 * loads the webpage
 * fetches the html and calls indexPage
 * prints out the index
 * and then deletes it
 */
static void indexBuild (char* pageDirectory, char* indexFile) {
  index_t* index = index_new(900);
  int docId = 1;
  webpage_t* page;
  while ((page = pagedir_load(pageDirectory, docId)) != NULL) {
    if (webpage_fetch(page)) {
      indexPage(index, page, docId);
    }
    webpage_delete(page);
    docId++;
  }
  FILE* fp;
  fp = fopen(indexFile, "w");
  if (fp == NULL) {
    fprintf(stderr, "Unable to write index file\n");
    exit(2);
  }
  pagedir_write(index, fp);
  fclose(fp);
  pagedir_delete(index);
}  


/******* indexPage *******/
/* reads words from webpages and inserts them into the index
 * before inserting, normalizes (makes all the letters lowercase) the words
 * ignores trivial words (len < 3)
 */
static void indexPage (index_t* index, webpage_t* page, int docID) {
  int pos = 0;
  char* word;
  while ((word = webpage_getNextWord(page, &pos)) != NULL) {
    if (strlen(word) > 2) {
      char* normWord = normalizeWord(word);
      index_insert(index, normWord, docID);
    }
    free(word);
  }
}     


/****** main *******/
// calls parseArgs and indexBuild
int main (const int argc, char* argv[]) {
  if (argc == 3) {
    parseArgs(argc, argv, argv[1], argv[2]);
    indexBuild(argv[1], argv[2]);
    return 0;
  }
  fprintf(stderr, "Incorrect number of arguments\n");
  exit(2);
}
