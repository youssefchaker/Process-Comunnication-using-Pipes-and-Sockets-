#include "serv_cli_fifo.h"

int main() {

  /* Déclarations */
  
  int sock = 0;
  struct sockaddr_in serv_addr;
  int rep[NMAX];
  int n,i,client_fd;

  /* Création de socket client */
  
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket creation failed");
        exit(1);
    }
    
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0) {
        perror("mauvais @");
        exit(2);
    }
    
  /* connection de socket client au socket serveur */
  
  if ((client_fd=connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) {
        perror("problem de connection");
        exit(3);
  }
  
  /* Construction et envoi d’une question */
  
  srand(getpid());
  n = rand()%NMAX+1;
  char ch[5];
  sprintf(ch, "%d", n);
  if(send(sock, ch, strlen(ch), 0)==-1){
  	perror("problem denvoie de question");
        exit(4);
  }
  
  /* Lecture de la réponse */
  
  if(read(sock, rep, sizeof(rep))<0){
  	perror("problem de reception de reponse");
        exit(5);
  }
    
  /* Traitement local de la réponse */
  
  printf("Reponse Retourner!!!\n");
  printf("la reponse est:\n");
  for (i = 0; i < n; i++) {
    printf("numero %d= %d\n", i + 1, rep[i]);
    fflush(stdout);
  }
  
  /* fermeture des sockets */

  close(client_fd);
  exit(6);

  return 0;
}
