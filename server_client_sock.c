#include "serv_cli_sock.h"

int main() {

  /*Déclarations */

  int server_fd, new_socket, n, j, i, sock, fork1, fork2;
  struct sockaddr_in address, serv_addr;
  int opt = 1;
  int addrlen = sizeof(address), rep[NMAX], client_fd;
  char buffer[1024] = {0};

  /* test fork */

  if ((fork1 = fork()) == -1 | (fork2 = fork()) == -1) {
    perror("error fork");
    exit(1);
  }

  /* SERVER*/
  if (fork2 == 0) {

    /* Création de socket serveur*/

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket creation failed");
      exit(2);
    }

    /* Configuration du socket */

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, & opt, sizeof(opt))) {
      perror("setsockopt");
      exit(3);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    /* Associer la socket avec une adresse et un numero du port */

    bind(server_fd, (struct sockaddr * ) & address, sizeof(address));
    /*initialisation du générateur de nombres aléatoires*/

    srand(getpid());

    while (1) {
      /* Attendre la requete de client */

      if (listen(server_fd, 10) < 0) {
        perror("listen error");
        exit(5);
      }

      /* Connection de client et creation de socket d'echange */

      if ((new_socket = accept(server_fd, (struct sockaddr * ) & address,
          (socklen_t * ) & addrlen)) < 0) {
        perror("accept error");
        exit(6);
      }

      /* lecture d’une question */

      if (read(new_socket, buffer, 1024) < 0) {
        perror("Reception de question error");
        exit(7);
      }
      n = atoi(buffer);

      /* construction de la réponse */

      int rep[n];
      for (j = 0; j < n; j++) {
        rep[j] = rand() % 10000;
      }

      /* envoi de la réponse */

      if (send(new_socket, & rep, sizeof(rep), 0) == -1) {
        perror("envoie de reponse error");
        exit(8);
      }

      /* fermeture de socket d'echange */

      close(new_socket);

    }
    /* fermeture de socket serveur */
    close(server_fd);

  }

  /* CLIENTS */
  else {

    /* Création de socket client */

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket creation failed");
      exit(9);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", & serv_addr.sin_addr) <= 0) {
      perror("mauvais @");
      exit(10);
    }

    /* connection de socket client au socket serveur */

    if ((client_fd = connect(sock, (struct sockaddr * ) & serv_addr, sizeof(serv_addr))) < 0) {
      perror("problem de connection");
      exit(11);
    }

    /* Construction et envoi d’une question */

    srand(getpid());
    n = rand() % NMAX + 1;
    char ch[5];
    sprintf(ch,"%d",n);
    if (send(sock, ch, strlen(ch), 0) == -1) {
      perror("problem denvoie de question");
      exit(12);
    }

    /* Lecture de la réponse */

    if (read(sock, rep, sizeof(rep)) < 0) {
      perror("problem de reception de reponse");
      exit(13);
    }

    /* Traitement local de la réponse */
    printf("Reponse Retourner!!!\n");
    printf("la reponse est:\n");
    for (i = 0; i < n; i++) {
      printf("numero %d= %d\n", i + 1, rep[i]);
    }

    /* fermeture des sockets */

    close(client_fd);
    exit(14);
  }

  return 0;
}