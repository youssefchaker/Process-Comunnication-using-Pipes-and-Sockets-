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
#define NMAX 10

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


/* handlers des signals*/
void hand_reveil_client() {
	printf("Reponse Pret!!!\n");	
}

void hand_reveil() {
	printf("Fin client!!\n");
}
void fin_serveur() {
	printf("Fin serveur!!!\n");
  exit(1);
}