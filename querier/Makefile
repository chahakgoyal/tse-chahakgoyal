# Makefile for 'set' module
#
# Chahak Goyal, Spring 2021
#
all: querier

LIBS = ../common/common.a ../libcs50/libcs50-given.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

querier: querier.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


querier.o: ../libcs50/webpage.h ../libcs50/hashtable.h ../libcs50/counters.h ../common/pagedir.h ../common/index.h ../common/word.h

.PHONY: test valgrind clean

test: all
	bash -v testing.sh


valgrind: querier
	valgrind ./querier

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

