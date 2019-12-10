all: client serve

client: DUMBclient.c DUMBclient_lib.c
	gcc -c -D_POSIX_SOURCE DUMBclient_lib.c
	gcc -o DUMBclient DUMBclient.c DUMBclient_lib.o

serve: DUMBserve.c DUMBserve_lib.c
	gcc -c -D_POSIX_SOURCE DUMBserve_lib.c
	gcc -o DUMBserve DUMBserve.c DUMBserve_lib.o

clean:
	rm -rf *.o  DUMBclient DUMBserve
