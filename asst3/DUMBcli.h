#ifndef _DUMBcli_H
#define _DUMBcli_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

/* general client-side MACROS */
#define USAGE "usage: ./DUMBclient <IPv4 ADDRESS> <PORT NUMBER>\n\n"\
	"\tIPv4 ADDRESS  is the address of the DUMBserver you wish to connect to.\n"\
	"\tPORT NUMBER is the corresponding port on that server.\n"\
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

/* MACROS for reporting status of client to user */
#define NO_CONNECT -1

/* function for reporting status of client to user */
void report(int);
/* attempt to connect to server 3 times */
int connect_to_server(char *, char *);


#endif
