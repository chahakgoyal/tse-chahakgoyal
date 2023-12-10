# Makefile for 'set' module
#
# Chahak Goyal, Spring 2021
#

PROG = crawler
OBJS = crawler.o  
LIBS = ../libcs50.a ../common/common.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: ../bag.h ../hashtable.h ../webpage.h ../common/pagedir.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: $(PROG)
	bash -v testing.sh
# expects a file `test.names` to exist; it can contain any text.
valgrind: $(PROG)
	valgrind ./$(PROG)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

