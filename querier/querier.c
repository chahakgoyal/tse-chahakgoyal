/*
 * querier.c
 *
 * Chahak Goyal, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/file.h"
#include "../common/index.h"
#include "../common/pagedir.h"
#include <ctype.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../common/word.h"
#include <unistd.h>

/**** declaring functions ****/
static counters_t* andQuery(counters_t* countersFirst, counters_t* countersSecond);
static void counters_merge_add(void* arg, const int key, const int count);
static counters_t* orQuery(counters_t* countersFirst, counters_t* countersSecond);
static void counters_merge_or(void* arg, const int key, const int count);
int fileno(FILE *stream);
static void getResult(counters_t* result);


/***** struct to store the count and docId of the result counter set ******/
typedef struct result {
  int docId;
  int count;
} result_t;

typedef struct resultArray {
  result_t** array;
  int size;
} resultArray_t;

/**** creates a new result struct *****/
static result_t* result_new(int docId, int count) {
  result_t* result = malloc(sizeof(result_t));
  if (result == NULL) {
    return NULL;
  } else {
    result->docId = docId;
    result->count = count;
  }
  return result;
}

/**** create a new resultArray struct *****/
static resultArray_t* resultArray_new(result_t** array, int size) {
  resultArray_t* resultArray = malloc(sizeof(resultArray_t));
  if (resultArray == NULL) {
    return NULL;
  } else {
    resultArray->array = array;
    resultArray->size = size;
  }
  return resultArray;
}

static void
prompt(void)
{
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? ");
  }
}

/***** get the result counter ******/
static counters_t* resultCounter(char* words[], int size, index_t* index) {
  // create a result counter
  counters_t* result = counters_new();
  int i = 0;
  // while there are elements to be traversed in an array
  while (i < size) {
    // set counter to counter set of i word
    counters_t* counter = index_getItem(index, words[i]);
    // cluster of ands
    while (strcmp(words[i+1], "or") != 0) {
      if (strcmp(words[i+1], "and") == 0) {
        counter = andQuery(counter, index_getItem(index, words[i+2]));
        i+=2;
      }
      // if there is no conjunction between two words then it should act like and
      else {
        counter = andQuery(counter, index_getItem(index, words[i+1]));
        i++;
      }
      // break out of the loop if reached the end of the array
      if (i == size - 1) {
        break;
      }
    }
    // union of result and counter
    result = orQuery(result, counter);
    if (i == size - 1) {
      counters_delete(counter);
      break;
    }
    // union if or
    if (strcmp(words[i+1], "or") == 0) {
      i+= 2;
      // if last element
      if (i == size - 1) {
        counter = index_getItem(index, words[i]);
        result = orQuery(result, counter);
        break;
      }
    }
    //    counters_delete(counter);
  }
  // return result
  return result;
}


/***** checks arguments if they are valid or not *****/
static void parseArgs (const int argc, char* argv[], char* pageDirectory, char* indexFilename) {
  // proceed only if arguments are equal to 3 otherwise exit
  if (argc == 3) {
    // proceed only if ./crawler file exists in the directory otherwise exit
    if (pagedir_validate(pageDirectory)) {
      FILE* fp;
      // if index file can be read, return otherwise exit
      fp = fopen(indexFilename, "r");
      if (fp != NULL) {
        fclose(fp);
        return;
      } else {
        fprintf(stderr, "Unable to write indexFile\n");
        exit(2);
      }
    } else {
      fprintf(stderr, "Unable to validate directory\n");
      exit(2);
    }
  } else {
    fprintf(stderr, "Incorrect number of arguments\n");
  }
}


/**** loads index into an index struct from the index file ****/
static index_t* loadIndex(char* indexFilename) {
  FILE *fp;
  // open file to read 
  fp = fopen(indexFilename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Unable to read file");
    exit(2);
  }
  // create a new index
  index_t* index = index_new(file_numLines(fp));
  char* word;
  // read words until reached EOF
  while ((word = file_readWord(fp)) != NULL) {
    int id;
    int count;
    // get id, count pairs
    while (fscanf(fp, "%d %d", &id, &count) == 2) {
      // save them in the index
      index_save(index, word, id, count);
    }
    // free the word
    free(word);
  }
  // close the file
  fclose(fp);
  // return the index
  return index;
}



/******* reads lines from stdin and loads them into words array *******/
static void readLines(char* indexFilename) {
  char* str;
  bool newQuery = true;
  char* word;
  bool query = true;
  // ask the user for query
  prompt();
  // read from stdin until EOF
  while ((str = file_readLine(stdin)) != NULL) {
    int size = 0;
    char** words = (char**) malloc(size*sizeof(char*));
    // get the length of the string
    int len = strlen(str);
    // for all characters
    for (int i = 0; i < len; i++) {
      // if bad character, print error message
      if (!isspace(str[i]) && !isalpha(str[i])) {
        query = false;
        printf("ERROR: Invalid query\n");
      }
      // if first character is alpha
      if (i == 0 && isalpha(str[i]) != 0) {
        // make a pointer
        word = &str[i];
        // increment size of array
        size++;
      }
      // if character is space
      else if (isspace(str[i]) != 0) {
        // and next char is alpha
        if (isalpha(str[i+1]) != 0) {
          // terminate the new substring
          str[i] = '\0';
          // pointer to a new substring
          word = &str[i+1];
          // increment size
          size++;
        }
      }
      // reallocate the memory of words
      words = (char**) realloc(words, size*sizeof(char*));
      // while words exists
      if (size != 0) {
        words[size-1] = word;
      }
    }
    // normalize words
    for (int i = 0; i < size; i++) {
      words[i] = normalizeWord(words[i]);
    }
    bool error = true;
    // if and/or are one after another throw error
    for (int i = 0; i < size - 1; i++) {
      if (strcmp(words[i], "and") == 0 || strcmp(words[i], "or") == 0) {
        if (strcmp(words[i+1], "and") == 0 || strcmp(words[i+1], "or") == 0) {
          error = false;
          printf("ERROR: Invalid query\n");
        }
      }
    }
    // if and/or in the starting or the end throw error
    if (strcmp(words[0], "and") == 0 || strcmp(words[0], "or") == 0 || strcmp(words[size-1], "and") == 0 || strcmp(words[size-1], "or") == 0) {
      printf("ERROR: Invalid query\n");
      newQuery = false;
    }
    if (size == 1) {
      printf("ERROR: Invalid query\n");
    }
    // if valid query, call parseLine
    if (error && query && newQuery) {
      index_t* index = loadIndex(indexFilename);
      counters_t* result = resultCounter(words, size, index);
      for (int i = 0; i < size; i++) {
        printf("%s", words[i]);
      }
      printf("\n");
      getResult(result);
      pagedir_delete(index);
    }
    // ask the user for new query
    prompt();
    free(words);
    free(str);
  }
}

/**** counters_iteration helper function to add to the array *****/
void counters_iteration(void* arg, const int key, const int count) {
  // takes struct as argument 
  resultArray_t* resultArray = arg;
  result_t** array = resultArray->array;
  int size = resultArray->size;
  // create a new element
  result_t* result = result_new(key, count);
  // if nothing exists at index 0 add to it
  if (array[0] == NULL) {
    array[0] = result;
  } else {  //otherwise shift elements and then add to index 0
    for (int i = size - 1; i >= 0; i--) {
      array[i+1] = array[i];
    }
    array[0] = result;
  }
}

/****** helper function to get the size of the counters set ******/
void itemfunc(void* arg, const int key, const int count) {
  int *namecount = arg;
  if( namecount != NULL && key >= 0 && count >= 0) {
    // increment counter
    (*namecount)++;
  }
}

/***** helper function to compare the values in array ******/
int cmpfunc(const void* a, const void* b) {
  return *(int*) a - *(int *)b;
}


/****** gwrResult function to sort the array ******/
static void getResult(counters_t* result) {
  // get the size of the counters set
  int namecount = 0;
  counters_iterate(result, &namecount, itemfunc);
  // allocate appropriate memory to array
  result_t** array = (result_t**)malloc(namecount*sizeof(result_t*));
  // initialize new data struct
  resultArray_t* counts = resultArray_new(array, namecount);
  counters_iterate(result, counts, counters_iteration);
  // sort the array and print it
  qsort(&array[0], counts->size, sizeof(result_t*), cmpfunc);
  for (int i = 0; i < counts->size; i++) {
    printf("%d %d\n", array[i]->docId, array[i]->count);
  }
  counters_delete(result);
  //  free(array);
  //  resultArray_delete(counts);
}

  

/******* set intersection ******/
counters_t* andQuery(counters_t* countersFirst, counters_t* countersSecond) {
  // create a new counter
  counters_t* ctrs = counters_new();
  // create an array to be passed in counters_iterate
  counters_t* ctrsArray[2] = {ctrs, countersSecond};
  counters_iterate(countersFirst, ctrsArray, counters_merge_add);
  return ctrsArray[0];
}

/***** helper function for andQuery ******/
void counters_merge_add(void* arg, const int key, const int count) {
  counters_t** ctrsArray = arg;
  // get the counts for both the counter sets
  int countFirst = count;
  int countSecond = counters_get(ctrsArray[1], key);
  // add the lowest number of count to the new counters set
  if (countFirst > countSecond) {
    counters_set(ctrsArray[0], key, countSecond);
  }
  else if (countSecond >= countFirst) {
    counters_set(ctrsArray[0], key, countFirst);
  }
}

/****** set union ******/
counters_t* orQuery(counters_t* countersFirst, counters_t* countersSecond) {
  // call counters_iterate
  counters_iterate(countersSecond, countersFirst, counters_merge_or);
  return countersFirst;
}

/***** helper function for set orQuery *****/
void counters_merge_or(void* arg, const int key, const int count) {
  // counts for both the counter sets
  counters_t* countersFirst = arg;
  int countSecond = count;
  int countFirst = counters_get(countersFirst, key);
  // add the sum of the counts
  counters_set(countersFirst, key, countFirst+countSecond);
}

/**** main function *****/
int main(const int argc, char* argv[]) {
  parseArgs(argc, argv, argv[1], argv[2]);
  readLines(argv[2]);
  return 0;
}
