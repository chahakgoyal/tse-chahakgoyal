# Makefile for 'set' module
#
# Chahak Goyal, Spring 2021
#
all: indexer indextest

LIBS = ../common/common.a ../libcs50/libcs50.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

indexer: indexer.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: indextest.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indexer.o: ../libcs50/webpage.h ../libcs50/hashtable.h ../libcs50/counters.h ../common/pagedir.h ../common/index.h ../common/word.h
indextest.o: ../libcs50/hashtable.h ../libcs50/counters.h ../common/index.h ../common/pagedir.h  

.PHONY: test valgrind clean

test: all
	bash -v testing.sh


valgrind: indexer
	valgrind ./indexer
	  indextest
	valgrind ./indextest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

