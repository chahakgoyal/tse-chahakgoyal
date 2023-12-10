#Implementation- SPEC

In this document we reference the Requirements Specification and Design Specification and focus on the implementation-specific decisions. Here we focus on the core subset:

Data structures
Control flow: pseudo code for overall flow, and for each of the functions
Detailed function prototypes and their parameters
Error handling and recovery
Testing plan


## Data Structures
We use arrays, indexes, and create a new struct to hold docIds and counts and another one to hold array of structs and size of array

## Control flow
The querier is implemented in one file with many functions

###main
The ```main``` simply calls
```parseArgs```
```readLines```

###parseArgs
validates directory
checks the number of arguments
validates the filename

###loadIndex
```creates a new index
   reads words from the file
         for each word, scan the corresponding id, count pairs
             save them in the index
   close the file
   return index
```

###readLines
```call prompt
   read from stdin until EOF
        check whether the query is contains bad characters or not
        if not invalid, chop it up into words
        save the words in an array
        normalize the words of the array
        check if query is invalid
        if not invalid, call resultCounter and getResult
```

### resultCounter
```create a new counters set result
   iterate through every word in words array
           create a new counters set counter and set it to the counters set of the current word
           while not hit "or"
                 if next word is and
                    call andQuery on it
                 else if next word is not a conjunction
                    call andQuery on it
                 break out of the loop once at last word
           call orQuery on result and counter
           if hit "or"
              increment counter
                        if last word
                           call orQuery
```

###getResult
``` iterate through the counters set once to get the size
    create a new struct of  arrays and size and set it to a new array and size
    call counters_iterate again
    call qsort on the built array
    print the array
```

###counters_iteration
```takes the struct that holds array and size as argument and is a helper function
   creates a new struct to hold the docId and score
   if no element at index 0
      add it
   else
        shift other elements and then add
```

###andQuery
```set intersection
   creates a new counters set
   gives as argument to counters_iterate, an array of second counter and new counter
         in counters_iterate func:
         compare the count of first counter and second counter
                 add the key and the smaller of two counts to new counter
```

###orQuery
```set Union
   gives as argument to counters_iterate, one of the counters
   in counters_iterate func:
   add to the counters, the sum of count of both of the counters key
```


            
##Detailed function prototypes and their parameters
```typedef struct result result_t;
typedef struct resultArray resultArray_t;
static result_t* result_new(int docId, int count);
static resultArray_t* resultArray_new(result_t** array, int size);
static void
prompt(void);
static counters_t* resultCounter(char* words[], int size, index_t* index);
static void parseArgs (const int argc, char* argv[], char* pageDirectory, char* indexFilename);
static index_t* loadIndex(char* indexFilename);
static void readLines(char* indexFilename);
static void getResult(counters_t* result);
counters_t* andQuery(counters_t* countersFirst, counters_t* countersSecond);
counters_t* orQuery(counters_t* countersFirst, counters_t* countersSecond);
int main(const int argc, char* argv[]);
```

##Error handling and recovery
All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out of memory messages are handled by non-exit zero status. We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.
All code uses defensive-programming tactics to catch and exit, e.g., if a function receives bad parameters.
That said, certain errors are caught and handled internally.

##Testing Plan
Here's an implementation specific testing plan:
We write a script testing.sh that calls querier multiple times:
1. invalid queries
2. invalid pageDirectory
3. invalid indexFilename
4. Incorrect number of arguments
5. Valgrind
6. Valid queries
