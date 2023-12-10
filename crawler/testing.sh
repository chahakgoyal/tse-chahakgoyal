#!/bin/bash
# Testing crawler
#
# Chahak Goyal, Spring 2021

#incorrect number of arguments
mkdir ../pageDirectory/incorrect
mkdir ../pageDirectory/incorrect/args
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/incorrect/args 

#flipped arguments
mkdir ../pageDirectory/incorrect/flipped
./crawler ../pageDirectory/incorrect/flipped "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" 0


#external URL
mkdir ../pageDirectory/incorrect/extn
./crawler "https://en.wikipedia.org/wiki/Algorithm" ../pageDirectory/incorrect/extn 0 


#directory doesn't exist
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/incorrect/dir 0


#maxDepth out of range
mkdir ../pageDirectory/incorrect/outofrange
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/incorrect/outofrange 11

#valgrind on moderately sized website
mkdir ../pageDirectory/valgrind
valgrind ./crawler "http://cs50tse.cs.dartmouth.edu/tse/wikipedia/" ../pageDirectory/valgrind 0



#crawl letters with depth 0
mkdir ../pageDirectory/letters
mkdir ../pageDirectory/letters/letters-0
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/letters/letters-0 0


#crawl letters with depth 1
mkdir ../pageDirectory/letters/letters-1
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/letters/letters-1 1


#crawl letters with depth 2
mkdir ../pageDirectory/letters/letters-2
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/letters/letters-2 2


#crawl letters with depth 10
mkdir ../pageDirectory/letters/letters-10
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/index.html" ../pageDirectory/letters/letters-10 10


#crawl letters with different seed page with depth 5
mkdir ../pageDirectory/letters/diffSeed
./crawler "http://cs50tse.cs.dartmouth.edu/tse/letters/C.html" ../pageDirectory/letters/diffSeed 5


#crawl toScrape with depth 0
mkdir ../pageDirectory/toScrape
mkdir ../pageDirectory/toScrape/toScrape-0
./crawler "http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html" ../pageDirectory/toScrape/toScrape-0 0


#crawl toScrape with depth 1
mkdir ../pageDirectory/toScrape/toScrape-1
./crawler "http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html" ../pageDirectory/toScrape/toScrape-1 1


#crawl toScrape with depth 2
mkdir ../pageDirectory/toScrape/toScrape-2
./crawler "http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html" ../pageDirectory/toScrape/toScrape-2 2


#crawl toScrape with depth 3
mkdir ../pageDirectory/toScrape/toScrape-3
./crawler "http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html" ../pageDirectory/toScrape/toScrape-3 3


#crawl wikipedia with depth 0
mkdir ../pageDirectory/wikipedia
mkdir ../pageDirectory/wikipedia/wikipedia-0
./crawler "http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html" ../pageDirectory/wikipedia/wikipedia-0 0


#crawl wikipedia with depth 1
mkdir ../pageDirectory/wikipedia/wikipedia-1
./crawler "http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html" ../pageDirectory/wikipedia/wikipedia-1 1


#crawl wikipedia with seed 'computer interaction' and depth 2
mkdir ../pageDirectory/wikipedia/wikipedia-2
./crawler "http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html" ../pageDirectory/wikipedia/wikipedia-2 2

