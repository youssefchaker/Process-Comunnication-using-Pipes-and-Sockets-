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

/* ecriture dans le ficher pour chaque affichage */
void filemanipsock(char *line){
	FILE *out_file = fopen("out.txt", "a"); 
	if (out_file == NULL) 
	{   
		printf("error d'ouverture de fichier\n"); 
		exit(-1); 
	}
	fputs(line,out_file); 
	fputs("\n",out_file); 
	fclose(out_file);
}