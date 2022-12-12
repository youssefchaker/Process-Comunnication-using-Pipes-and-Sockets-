#include "serv_cli_fifo.h"

int main() {

  /*Déclarations */
  
  int server_fd, new_socket,n,j;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = { 0 };

  /* Création de socket serveur*/
  
  if ((server_fd = socket(AF_INET, SOCK_STREAM , 0)) < 0) {
        perror("socket creation failed");
        exit(1);
    }
    
  /* Configuration du socket */
  
  if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR, &opt,sizeof(opt))) {
        perror("setsockopt");
        exit(2);
    }
  
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
  /* Associer la socket avec une adresse et un numero du port */
  
  if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0) {
        perror("bind failed");
        exit(3);
  }
  
  /*initialisation du générateur de nombres aléatoires*/
  
  srand(getpid());
  
  
    while(1){
    /* Attendre la requete de client */
  
    if (listen(server_fd, 10) <0 ) {
        perror("listen error");
        exit(4);
    }
    
    /* Connection de client et creation de socket d'echange */
  
  if ((new_socket= accept(server_fd, (struct sockaddr*)&address,
  (socklen_t*)&addrlen))< 0) {
        perror("accept error");
        exit(5);
    }
  
    /* lecture d’une question */
    
    if(read(new_socket, buffer, 1024)<0){
    	perror("Reception de question error");
        exit(6);
    }
    n=atoi(buffer);
    printf("%d",n);
	
    /* construction de la réponse */
   
    int rep[n]; 
    for (j = 0; j < n; j++) {
      rep[j] = rand()%10000;
    }

    /* envoi de la réponse */
    
    if(send(new_socket, &rep, sizeof(rep),0)==-1){
    	perror("envoie de reponse error");
        exit(7);
    }
    
    /* fermeture de socket d'echange */
    
    close(new_socket);

} 
  /* fermeture de socket serveur */
  close(server_fd);
  return 0;
}
