
CC = gcc
CFLAGS = -g -Wall

default:	llistTester

llistTester:	llistTester.o llist.o
	$(CC) $(CFLAGS) $(LDFLAGS) llistTester.o llist.o -o $@


llistTester.o:	llistTester.c llist.c llist.h
	$(CC) $(CFLAGS) -c $< -o $@

llist.o:	llist.c llist.h
	$(CC) $(CFLAGS) -c $< -o $@			


clean:	
	$(RM) llistTester.o llist.o llistTester
