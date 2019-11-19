all:
	@echo "*** error:"
	@echo "Target not recognized. Did you mean 'make proc' or 'make thread'?"

proc: searchtest.c multitest_proc.o
	gcc searchtest.c multitest_proc.o -o proctest

multitest_proc.o: multitest_proc.c multitest.h
	gcc -c multitest_proc.c

thread: searchtest.c multitest_thread.o
	gcc searchtest.c multitest_thread.o -o threadtest

multitest_thread.o: multitest_thread.c multitest.h
	gcc -c -lpthread multitest_thread.c

clean:
	rm proctest threadtest; rm multitest_proc.o; rm multitest_thread.o
