PROG= main
APP1=server_client_fifo
APP2=server_client_sock
CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0`
TUBE1=fifo1
TUBE2=fifo2
run: app1 app2 main go 

app1: ${APP1}.c
		${CC} ${APP1}.c -o ${APP1}

app2: ${APP2}.c
		${CC} ${APP2}.c -o ${APP2}

main: ${PROG}.c
		${CC} ${CFLAGS} -o ${PROG} ${PROG}.c ${LIBS} -lX11

go: ${PROG}.c
		./${PROG}
clean:
	 	rm ${PROG}
		rm ${APP1}
		rm ${APP2}
		rm ${TUBE1}
		rm ${TUBE2}
		
