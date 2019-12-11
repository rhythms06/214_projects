#include "DUMBser.h"


int build_server_socket(char* portno)
{
	struct addrinfo 	ai;
	struct addrinfo* 	result;
	int					sfd, s, optval;
	
	memset(&ai, 0, sizeof(struct addrinfo));
	ai.ai_family = AF_INET;			// IPv4
	ai.ai_socktype = SOCK_STREAM;	// TCP socket
	ai.ai_flags = AI_PASSIVE;		// wildcard IP to bind(2) to all interfaces
	ai.ai_canonname = NULL;			
	ai.ai_addr = NULL;				
	ai.ai_next = NULL;			

	/* build the addrinfo struct 'result' based on options set above */
	s = getaddrinfo(NULL, portno, &ai, &result);
	if(s != 0)
	{	/* error building struct addrinfo result */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, gai_strerror(s));
		freeaddrinfo(result);
		exit(EXIT_FAILURE);
	}

	/* open the socket */
	sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(sfd == -1)
	{	/* socket(2) failed */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
		freeaddrinfo(result);
		exit(EXIT_FAILURE);
	}

	/* socket option SO_REUSEADDR deactivates the time between a port closing
	 * and it being available to bind to again */
	optval = 1;
	if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) != 0)
	{	/* setsockopt(2) failed */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
		freeaddrinfo(result);
		close(sfd);
		exit(EXIT_FAILURE);
	}

	/* bind socket to port portno */
	if(bind(sfd, result->ai_addr, result->ai_addrlen) != 0)
	{	/* bind(2) failed */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
		freeaddrinfo(result);
		close(sfd);
		exit(EXIT_FAILURE);
	}
	
	/* socket bound successfuly. return socket file descriptor */
	freeaddrinfo(result);
	return sfd;
}

void* client_thread(void* c)
{
	/* get client info */
	client cli = *(client *)c;
	int sfd = cli.sfd;
	char* cip = cli.c_ip;

	pthread_detach(pthread_self());
	report_success(sfd, cip, "connected");



		

	return;
}


void report_success(int sfd, char* c_addr, char* cmd)
{
	time_t now; time(&now); char tstmp[26];
	asctime_r(localtime(&now), tstmp); strtok(tstmp, "\n");
	fprintf(stdout, "%s %s %s\n", tstmp, c_addr, cmd);
	return;
}


void serve_dat_shit_up(int sfd)
{
	socklen_t			sl;
	struct sockaddr_in	saddr;
	int					fd, thread_count;
	int*				fdp;
	pthread_t			tid;

	/* mark sfd as a passive socket that will be used to accept incoming
	 * requests using accept(2) */
	if(listen(sfd, 128) != 0)
	{	/* listen(2) failed */
		fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(errno));
		close(sfd);
		exit(EXIT_FAILURE);
	}

	/* accept new connections.
	 * accept(2) will queue any connect request made; the queue can grow up to 128 requests.
	 * accept(2) will block if the queue is empty. */
	sl = sizeof(saddr);
	thread_count = 0;
	while ( (fd = accept(sfd, (struct sockaddr*)&saddr, &sl) != -1) )
	{
		/* build client struct to pass client data to new thread.
		 * include file descriptor for client socket, and client's IP address */
		client* client_id = (client*)malloc(sizeof(client));
		client_id->sfd = fd;
		client_id->c_ip = (char*)malloc(INET_ADDRSTRLEN);
		struct sockaddr_in* ipv4addr= (struct sockaddr_in*)&saddr;
		struct in_addr ipaddr = ipv4addr->sin_addr;
		inet_ntop(AF_INET, &ipaddr, client_id->c_ip, INET_ADDRSTRLEN);

		/* spawn thread for connected client */
		int t_status = pthread_create(&tid, NULL, client_thread, (void *)client_id);
		if(t_status != 0)
		{	/* thread failed to spawn */
			fprintf(stderr, "error in %s on line %d: %s\n", __FILE__, __LINE__, strerror(t_status));
			return;
		}
	}
	return;
}
