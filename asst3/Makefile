all: client serve

client: DUMBclient.c
	gcc -o DUMBclient DUMBclient.c

serve: DUMBserver.c
	gcc -o DUMBserve DUMBserver.c

clean:
	rm -f DUMBclient DUMBserve
