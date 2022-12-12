#include "serv_cli_fifo.h"

#include "Handlers_Serv.h"

int main() {
  /*Déclarations */
  int tube1,tube2,n,j;
  struct QR qr;

  /* Création des tubes nommés */
  mkfifo(PATH1, 0666);
  mkfifo(PATH2, 0666);

  /*initialisation du générateur de nombres aléatoires*/
  srand(getpid());

  /* Ouverture des tubes nommés */
  if ((tube1 = open(PATH1, O_RDWR)) == -1) {
    perror("fopen");
    exit(1);
  }
  if ((tube2 = open(PATH2, O_WRONLY)) == -1) {
    perror("fopen");
    exit(1);
  }

  /* Installation des Handlers */
  signal(SIGUSR1, hand_reveil);
  signal(SIGQUIT, fin_serveur);
  while (1) {
    /* lecture d’une question */
    read(tube1, &qr, sizeof(qr));
    /* construction de la réponse */
    n = qr.quest;
    for (j = 0; j < n; j++) {
      qr.rep[j] = rand()%10000;
    }

    /* envoi de la réponse */
    qr.numserv = getpid();
    write(tube2, &qr, sizeof(qr));
    /* envoi du signal SIGUSR1 au client concerné */
    kill(qr.numproc, SIGUSR1);
    pause();
  }
  return 0;
}
