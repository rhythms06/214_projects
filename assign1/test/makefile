all: test

test: test.c mymalloc.o
	gcc test.c mymalloc.o -o test

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

clean:
	rm test mymalloc.o
