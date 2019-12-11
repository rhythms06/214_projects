all: client serve

client: DUMBclient.c DUMBclient_lib.c
	gcc -c -D_POSIX_SOURCE DUMBclient_lib.c
	gcc -o DUMBclient DUMBclient.c DUMBclient_lib.o

serve: DUMBserve.c DUMBserve_lib.c
	gcc -c -pthread -D_POSIX_SOURCE DUMBserve_lib.c
	gcc -pthread DUMBserve.c DUMBserve_lib.o -o DUMBserve

clean:
	rm -rf *.o  DUMBclient DUMBserve
