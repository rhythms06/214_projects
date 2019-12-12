#include "DUMBser.h"

int main(int argc, char** argv)
{
	if(argc != 2) 
	{	/* Invalid number of arguments */
	fprintf(stderr, "%s", USAGE); 
	exit(EXIT_FAILURE);
	}
	int portno = atoi(argv[1]);
	if(portno < 4096 || portno > 65535)
	{	/* error: port number is out of range */
		fprintf(stderr, "error: port number out of acceptable range.\n"
						"%s", USAGE);
		exit(EXIT_FAILURE);
	}

	/* open and bind server socket */
	int			sfd;
	sfd = build_server_socket(argv[1]);

	/* listen, accept, and serve */
	serve_dat_shit_up(sfd);

	close(sfd);
	exit(EXIT_SUCCESS);

	/* Commands to listen for and respond to:
	HELLO
	quit			(which causes: E.1 GDBYE)
	create		(which causes: E.2 CREAT)
	delete		(which causes: E.6 DELBX)
	open		(which causes: E.3 OPNBX)
	close		(which causes: E.7 CLSBX)
	next			(which causes: E.4 NXTMG)
	put			(which causes: E.5 PUTMG)
	*/

}
