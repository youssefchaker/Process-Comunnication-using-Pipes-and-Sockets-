#include "serv_cli_fifo.h"

#include "Handlers_Cli.h"

int main() {
  /* Déclarations */
  int n = 0;
  int i = 0;
  int tube1;
  int tube2;
  struct QR qr;
  /* Ouverture des tubes nommés */
  if ((tube1 = open(PATH1, O_WRONLY)) == -1) {
    perror("fopen");
    exit(1);
  }
  if ((tube2 = open(PATH2, O_RDONLY)) == -1) {
    perror("fopen");
    exit(1);
  }

  /* Installation des Handlers */
  signal(SIGUSR1, hand_reveil);
  /* Construction et envoi d’une question */
  qr.numproc = getpid();
  srand(getpid());
  n = rand()%NMAX+1;
  qr.quest = n;
  write(tube1,&qr, sizeof(qr));

  /* Attente de la réponse */
  pause();
  /* Lecture de la réponse */
  read(tube2,&qr, sizeof(qr));
  /* Envoi du signal SIGUSR1 au serveur */
  kill(qr.numserv, SIGUSR1);
  /* Traitement local de la réponse */
  printf("Reponse Retourner!!!\n");
  printf("la reponse est:\n");
  for (i = 0; i < n; i++) {
    printf("numero %d= %d\n", i + 1, qr.rep[i]);
    fflush(stdout);
  }
  return 0;
}
