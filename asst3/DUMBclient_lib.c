#include "DUMBcli.h"

int connect_to_server(char* serv_addr, char* portno)
{
	struct 	addrinfo ai;
	struct 	addrinfo* result;
	char 	buf[256];
	int 	sfd, s, i;

	memset(&ai, 0, sizeof(struct addrinfo));
	ai.ai_family = AF_INET;			// IPv4 only
	ai.ai_socktype = SOCK_STREAM;	// TCP socket

	s = getaddrinfo(serv_addr, portno, &ai, &result);
	if(s != 0)
	{ /* getaddrinfo(...) returns 0 on success, otherwise returns an error code */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* build socket */
	sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(sfd < 0)
	{ 	/* socket failed */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, gai_strerror(s));
		freeaddrinfo(result);
		exit(EXIT_FAILURE);
	}
	else
	{	/* socket succeeded */
		i = 0;
		while(i < 3)
		{	/* attempt to connect to server maximum of 3 times */
			if(connect(sfd, result->ai_addr, result->ai_addrlen) == -1)
			{	/* connected failed */
				sleep(2);
				fprintf(stdout, "connecting to %s ... [%d]\n", serv_addr, i);
				i++;
			}
			else
			{	/* connected succeeded */
				freeaddrinfo(result);
				return sfd;
			}
		}
	}
	/* connection to server failed */
	fprintf(stderr, "connection to server failed.\n"
					"error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
	freeaddrinfo(result);
	close(sfd);
	exit(EXIT_FAILURE);
}

void get_busy_clienting(int sfd)
{
	/* buffer for sending DUMB commands */
	char cmd[4096] = {'0'};

	/* initiate session with a DUMB server */
	strcpy(cmd, "HELLO\0");
	write(sfd, cmd, 4096);

	char reply[4096] = {'0'};
	int bytes_read = read(sfd, reply, 2048);

	// printf("received reply (%d bytes):\n", bytes_read);
	// printf("%s\n", reply);

	if(bytes_read < 0)
	{	/* error reading */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
		return;
	}
	else if(strcmp(reply, "HELLO DUMBv0 ready!\0") == 0)
	{	/* session has been initiated */
		fprintf(stdout, "Session has been initiated with DUMB server.\n");
	}
	else
	{	/* strange response to HELLO */
		fprintf(stderr, "Session was not initiated. Try again later.\n");
		return;
	}

	int active = 1;
	int shouldWR = 0;
	char* buff = NULL;
	size_t maxSize = 4096;

	while(active)
	{
	getline(&buff, &maxSize, stdin);

	if(strcmp(buff, "create\n") == 0)
	{
		printf("create:> ");
		char* boxName = NULL;
		getline(&boxName, &maxSize, stdin);
		sprintf(cmd, "CREAT %s", boxName);
		free(boxName);
		shouldWR = 1;
	}
	else if(strcmp(buff, "open\n") == 0)
	{
		printf("open:> ");
		char* boxName = NULL;
		getline(&boxName, &maxSize, stdin);
		sprintf(cmd, "OPENBX %s", boxName);
		free(boxName);
		shouldWR = 1;
	}
	else if(strcmp(buff, "next\n") == 0)
	{
		strcpy(cmd, "NXTMSG\0");
		shouldWR = 1;
	}
	else if(strcmp(buff, "put\n") == 0)
	{
		printf("put:> ");
		char* msg = NULL;
		getline(&msg, &maxSize, stdin);
		int msgLength = strlen(msg);
		sprintf(cmd, "PUTMG!%d!%s", msgLength, msg);
		free(msg);
		shouldWR = 1;
	}
	else if(strcmp(buff, "delete\n") == 0)
	{
		printf("delete:> ");
		char* boxName = NULL;
		getline(&boxName, &maxSize, stdin);
		sprintf(cmd, "DELBX %s", boxName);
		free(boxName);
		shouldWR = 1;
	}
	else if(strcmp(buff, "close\n") == 0)
	{
		printf("close:> ");
		char* boxName = NULL;
		getline(&boxName, &maxSize, stdin);
		sprintf(cmd, "CLSBX %s", boxName);
		free(boxName);
		shouldWR = 1;
	}
	else if(strcmp(buff, "quit\n") == 0)
	{
		strcpy(cmd, "GDBYE\0");
		shouldWR = 1;
	}
	else if(strcmp(buff, "help\n") == 0)
	{
		printf("You can send the following commands:\n");
		printf("'quit' (which causes GDBYE)\n");
		printf("'create' (which causes CREAT)\n");
		printf("'delete' (which causes DELBX)\n");
		printf("'open' (which causes OPNBX)\n");
		printf("'close' (which causes CLSBX)\n");
		printf("'next' (which causes NXTMG)\n");
		printf("'put' (which causes PUTMG)\n");
		printf("'help' (which lists these commands)\n");

	}
	else
	{
		printf("invalid command. try 'help'.\n");
	}
	if(shouldWR == 1)
	{
		write(sfd, cmd, 4096);
		bytes_read = read(sfd, reply, 2048);

		// printf("received reply (%d bytes):\n", bytes_read);
		// printf("%s\n", reply);

		if(bytes_read < 0)
		{	/* error reading */
			fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
		}
		else
		{
			printf("%s", reply);
		}
	}
	}

	free(buff);



	return;
}
