TARGET=client server 
CLIENT=client
SERVER=server
CLIENTS= clientscript
CC=gcc
CFLAGS= -Wall -Wextra -g
rs: server runs
rc: client runc  
normal: $(TARGET)
client: client.c
	$(CC) $(CFLAGS) client.c -o client
server: server.c
	$(CC) $(CFLAGS) server.c -o server
clean:
	$(RM) $(TARGET)
runs: $(SERVER)
	./${SERVER}
runc: $(CLIENT)
	./$(CLIENT)
rcs: ${CLIENTS}
	./${CLIENTS}