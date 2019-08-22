.PHONY:clean
.PHONY:test

CC = gcc
CFLAGS = -Wall -g

main:test.c hash_table.o prime.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

hash_table.o:hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $< -o $@
prime.o:prime.c prime.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f hash_table.o prime.o main

test:
	./main