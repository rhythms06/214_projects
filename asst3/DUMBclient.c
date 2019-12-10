#include "DUMBcli.h"

int main(int argc, char** argv)
{
	if(argc != 3) 
	{	/* Invalid number of arguments */
		fprintf(stdout, "%s", USAGE);
		exit(EXIT_SUCCESS);
	}

	int	sfd;	// server socket descriptor

	sfd = connect_to_server(argv[1], argv[2]);
	close(sfd);	

	/* Commands to implement:
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
