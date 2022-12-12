/* bib systems*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
/* nb max de triage*/
#define NMAX 50

/* paths des tubes nommes*/
#define PATH1 "fifo1"
#define PATH2 "fifo2"

/* decl de struct des questions/reponses*/
struct QR { 
  int numproc;  
  int numserv;
  int quest;           
  int rep[NMAX];       
};
