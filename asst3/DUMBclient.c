#include "DUMBcli.h"

int main(int argc, char** argv)
{
  if(argc != 3) /* check out 'man 3 getopt' */
  {
    // Invalid number of arguments.
	errno = EINVAL ;
	fprintf(stderr, "%s\n%s\n", strerror(errno), "usage...");
	exit(EXIT_FAILURE);
  }
  char* addr = argv[1];
  // 'addr' is the IP address or hostname the user wants to connect to.
  int portno = atoi(argv[2]);
  // 'portno' is the port the user wants to connect to.
  // Note that DUMB servers listen only on port numbers >4K.
  // Also note that atoi() -> 0 when a conversion cannot be performed.

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

  return 0;
}
