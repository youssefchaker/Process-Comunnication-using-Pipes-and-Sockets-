/* bib systems*/ 
#include <stdio.h>

#include <stdlib.h>

#include <signal.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <unistd.h>

#include <fcntl.h>

#include <sys/wait.h>

#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

#include <arpa/inet.h>

/* port de communication */
#define PORT 2000

/* nb max de triage*/
#define NMAX 10