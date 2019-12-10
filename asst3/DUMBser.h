#ifndef _DUMBser_H
#define _DUMBser_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

/* general server-side MACROS */
#define USAGE "usage: ./DUMBserve <PORT NUMBER>\n\n"\
	"\tPORT NUMBER is the port on the server that will listen for DUMB client connections.\n"\
	"\tPlease enter a port number in range [4096 : 65,535]\n\n"\
	"That's it, that's all folks!\n"


/* define COMMANDS as integers (may not need)*/
#define HELLO 0
#define GDBYE 1
#define CREAT 2
#define OPNBX 3
#define NXTMS 4
#define PUTMG 5
#define DELBX 6
#define CLSBX 7

/* server side functions */
int build_server_socket(char *);
void serve_dat_shit_up(int);


#endif
