#include "DUMBser.h"

int main(int argc, char** argv)
{
  if(argc != 2) /* check out 'man 3 getopt' */
  {
    // Invalid number of arguments.
	errno = EINVAL ;
	fprintf(stderr, "%s\n%s\n", strerror(errno), "usage...");
	exit(EXIT_FAILURE);
  }
  int portno = atoi(argv[1]);
  // 'portno' is the port at which the user wants to create a server.
  // It should be larger than 4K (not base-10, whatever that means).
  // Also note that atoi() -> 0 when a conversion cannot be performed.

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

  return 0;
}
