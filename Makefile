.PHONY:clean
.PHONY:test

CC = gcc
CFLAGS = -Wall -g

main:test.c hash_table.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

hash_table.o:hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf hash_table.o main

test:
	./main
