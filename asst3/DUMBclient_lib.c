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
	if(sfd == -1)
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
	/* buffers for sending DUMB commands and receiving responses from DUMB server */
	char cmd[CMD_LEN] = {'0'};
	char reply[4096] = {'0'};
	int bytes_read = 0;

	/* initiate session with a DUMB server */
	strcpy(cmd, "HELLO\0");
	write(sfd, cmd, CMD_LEN);
	bytes_read = read(sfd, reply, 2048);

	printf("%s\n", reply);

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

	return;
}

