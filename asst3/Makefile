all: client serve

client: DUMBclient.c DUMBcli_lib.c
	gcc -c -D_POSIX_SOURCE DUMBcli_lib.c
	gcc -o DUMBclient DUMBclient.c DUMBcli_lib.o

serve: DUMBserver.c DUMBser_lib.c
	gcc -c -D_POSIX_SOURCE DUMBser_lib.c
	gcc -o DUMBserve DUMBserver.c DUMBser_lib.o

clean:
	rm -rf *.o  DUMBclient DUMBserve
