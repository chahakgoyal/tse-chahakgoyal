#!/bin/bash

# incorrect number of arguments
./indexer
./indexer ~/cs50-dev/shared/tse/output/letters-1
./indexer ~ ~/cs50-dev/shared/tse/output/letters-1 index.out

# invalid pageDirectory
./indexer ~/cs50-dev/tse/output/letters-1 index.out

# invalid indexFile
./indexer ~/cs50-dev/shared/tse/output/letters-1 ~/cs50-dev/tse/index.out

# not a crawler directory
./indexer ./ index.out

# read only indexFile
./indexer ~/cs50-dev/shared/tse/output/letters-1 ~/cs50-dev/shared/tse/output/letters-1.index

### valid arguments

# letters-1
mkdir letters
mkdir letters/letters-1
./indexer ~/cs50-dev/shared/tse/output/letters-1 letters/letters-1/letters-1.out
./indextest letters/letters-1/letters-1.out letters/letters-1/letters-1.index

# letters-0
mkdir letters/letters-0
./indexer ~/cs50-dev/shared/tse/output/letters-0 letters/letters-0/letters-0.out
./indextest letters/letters-0/letters-0.out letters/letters-0/letters-0.index

# letters-3
mkdir letters/letters-3
./indexer ~/cs50-dev/shared/tse/output/letters-3 letters/letters-3/letters-3.out
./indextest letters/letters-3/letters-3.out letters/letters-3/letters-3.index

# toscrape-0
mkdir toscrape
mkdir toscrape/toscrape-0
./indexer ~/cs50-dev/shared/tse/output/toscrape-0 toscrape/toscrape-0/toscrape-0.out
./indextest toscrape/toscrape-0/toscrape-0.out toscrape/toscrape-0/toscrape-0.index

# toscrape-1
mkdir toscrape/toscrape-1
./indexer ~/cs50-dev/shared/tse/output/toscrape-1 toscrape/toscrape-1/toscrape-1.out 
./indextest toscrape/toscrape-1/toscrape-1.out toscrape/toscrape-1/toscrape-1.index 

# toscrape-2
mkdir toscrape/toscrape-2
./indexer ~/cs50-dev/shared/tse/output/toscrape-2 toscrape/toscrape-2/toscrape-2.out                                                                        
./indextest toscrape/toscrape-2/toscrape-2.out toscrape/toscrape-2/toscrape-2.index 

# wikipedia-0
mkdir wiki
mkdir wiki/wiki-0
./indexer ~/cs50-dev/shared/tse/output/wikipedia-0 wiki/wiki-0/wiki-0.out
./indextest wiki/wiki-0/wiki-0.out wiki/wiki-0/wiki-0.index

# wikipedia-1
mkdir wiki/wiki-1
./indexer ~/cs50-dev/shared/tse/output/wikipedia-1 wiki/wiki-1/wiki-1.out
./indextest wiki/wiki-1/wiki-1.out wiki/wiki-1/wiki-1.index

# valgrind on letters-10
mkdir letters/letters-10
valgrind ./indexer ~/cs50-dev/shared/tse/output/letters-10 letters/letters-10/letters-10.out
valgrind ./indextest letters/letters-10/letters-10.out letters/letters-10/letters-10.index
