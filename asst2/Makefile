all:
	$(error make with target 'proc' or 'thread')

proc: searchtest.c multitest_proc.o
	gcc -lm searchtest.c multitest_proc.o -o proctest

multitest_proc.o: multitest_proc.c multitest.h
	gcc -c -lm multitest_proc.c

thread: searchtest.c multitest_thread.o
	gcc -lm -lpthread searchtest.c multitest_thread.o -o threadtest

multitest_thread.o: multitest_thread.c multitest.h
	gcc -c -lpthread multitest_thread.c

clean:
	rm proctest threadtest; rm multitest_proc.o; rm multitest_thread.o


### the below can be used for testing ###

proc_test: tmp.c proc_test.o
	gcc -lm tmp.c proc_test.o -o tmper

proc_test.o: proc_test.c multitest.h
	gcc -c -lm proc_test.c

thread_test: tmp.c thread_test.o
	gcc -lm -lpthread tmp.c thread_test.o -o ttmper

thread_test.o: thread_test.c multitest.h
	gcc -c -lpthread -lm thread_test.c

clean_test:
	rm tmper proc_test.o ttmper thread_test.o


