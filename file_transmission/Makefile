CC     =    gcc
FILE   =    Makefile headers.c headers.h ft_server.c ft_client.c
OBJ    =    server client
OBJ_U  =    headers.o files.o
DIR    =    file_transmission

server: ft_server.c
	gcc -o server ft_server.c

client: ft_client.c
	gcc -o client ft_client.c

all:
	$(CC) -c headers.c files.c
	$(CC) $(OBJ_U) -w ft_server.c -o server
	$(CC) $(OBJ_U) -w ft_client.c -o client

.c.o:
	$(CC) -c $<

clean: rm $(OBJ) $(OBJ_U)
