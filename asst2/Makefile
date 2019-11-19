all:
<<<<<<< HEAD
	$(error Target not recognized. Did you mean 'make proc' or 'make thread'?)
=======
	@echo "*** error:"
	@echo "Target not recongized. Did you mean 'make proc' or 'make thread'?"
>>>>>>> 3e5409d0a0afdaadb627c53a7180f1fbded16cfb

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
