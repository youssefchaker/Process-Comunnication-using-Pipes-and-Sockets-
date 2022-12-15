#include "serv_cli_fifo.h"

int main() {

  /* Déclarations */

  int tube1, tube2, n, j, i, fork1, fork2;
  struct QR qr;

  /* test fork */

  if (((fork1 = fork()) == -1) | ((fork2 = fork()) == -1)) {
    perror("error fork");
    exit(3);
  }

  /* SERVER*/
  if (fork2 == 0) {

    /* Création des tubes nommés */
    mkfifo(PATH1, 0666);
    mkfifo(PATH2, 0666);

    /*initialisation du générateur de nombres aléatoires*/
    srand(getpid());

    /* Ouverture des tubes nommés */
    if ((tube1 = open(PATH1, O_RDWR)) == -1) {
      perror("fopen");
      exit(3);
    }
    if ((tube2 = open(PATH2, O_WRONLY)) == -1) {
      perror("fopen");
      exit(4);
    }

    /* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);
    signal(SIGQUIT, fin_serveur);
    while (1) {
      /* lecture d’une question */
      read(tube1, & qr, sizeof(qr));
      /* construction de la réponse */
      n = qr.quest;
      for (j = 0; j < n; j++) {
        qr.rep[j] = rand() % 10000;
      }

      /* envoi de la réponse */
      qr.numserv = getpid();
      write(tube2, & qr, sizeof(qr));
      /* envoi du signal SIGUSR1 au client concerné */
      kill(qr.numproc, SIGUSR1);
      pause();
    }
  }

  /* CLIENT */
  else {
    /* Ouverture des tubes nommés */
    if ((tube1 = open(PATH1, O_WRONLY)) == -1) {
      perror("fopen");
      exit(1);
    }
    if ((tube2 = open(PATH2, O_RDONLY)) == -1) {
      perror("fopen");
      exit(2);
    }

    /* Installation des Handlers */
    signal(SIGUSR1, hand_reveil_client);
    /* Construction et envoi d’une question */
    qr.numproc = getpid();
    srand(getpid());
    n = rand() % NMAX + 1;
    qr.quest = n;
    write(tube1, & qr, sizeof(qr));

    /* Attente de la réponse */
    pause();
    /* Lecture de la réponse */
    read(tube2, & qr, sizeof(qr));
    /* Envoi du signal SIGUSR1 au serveur */
    kill(qr.numserv, SIGUSR1);
    /* Traitement local de la réponse */
    printf("Reponse Retourner!!!\n");
    printf("la reponse est:\n");
    for (i = 0; i < n; i++) {
      printf("numero %d= %d\n", i + 1, qr.rep[i]);
      fflush(stdout);
    }
  }

  return 0;
}