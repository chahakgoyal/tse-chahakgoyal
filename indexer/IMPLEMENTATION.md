# Implementation Spec

## Indexer

### Functions that can be used to write indexer.c
1. ```parseArgs```
2. ```indexBuild```
3. ```indexPage```
4. ```main```

### Here's the psuedocode of the functions

1. ```parseArgs```
```
check the number of arguments
      check if directory given is valid (has .crawler file)
```

2. ```indexBuild```
```
create a new index
load webpage from the pagedirectory and docID
     fetch the webpage
           call indexPage
     delete the webpage
open new index file
write the index to index file
delete the index
```

3. ```indexPage```
```
read words from webpage
     if words are non-trivial
        normalize the word
        insert word in index
     free the word
```

4. ```main```
```
call parseArgs
call indexBuild
```

### Defining functions

```
static void parseArgs(const int argc, char* argv[], char* pageDirectory, char* indexFilename);
static void indexBuild(char* pageDirectory, char* indexFile);
static void indexPage(index_t* index, webpage_t* load, int docID);
int main(const int argc, char* argv[]);
```


### Testing Plan
Test with incorrect number of arguments: 0, 2, 4
Test with non-existent pageDirectory
Test with non-existent pathname to indexFile
Test with a directory that does not have a ```.crawler``` file
Test with an indexFile that is read only
Testing with valid arguments:
Letters: 0,1,3
ToScrape: 0,1,2
Wikipedia: 0,1
Valgrind: Letters-10
Save the output in testing.out