#Design Spec
In this document we reference the Requirements Specification and focus on the implementation-independent design decisions. Here we focus on the core subset:

User interface
Inputs and outputs
Functional decomposition into modules
Pseudo code (plain English-like language) for logic/algorithmic flow
Major data structures
Testing plan

#User Interface
As described in the Requirements Spec, run the querier using
```querier pageDirectory indexFilename```

For example:
```./querier ~/cs50-dev/shared/tse/output/letters-2 ~/cs50-dev/shared/tse/output/letters-2.index```

#Inputs and Outputs
As per the requirements spec,
Inputs will be words separated by and/or
Output will be the list of documents satisfying the input with the scores

#Functional decomposition into modules
Modules from previous labs as well as querier

#Pseudo Code
```parse the command line, validate parameters
   load index from the indexfile
   make arrays of words 
   from array of words
        parse the words accordingly
   return the finished counter set
   print the documents in descending order```

#Major Data Structures
1. A struct to hold docIds and scores
2. Arrays
3. Index
4. A struct to hold array of structs and size

# Testing Plan
Sample tests will run:
invalid queries
valid queries
invalid directory
invalid filename