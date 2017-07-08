#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "headers.h"
#include "files.h"

#define PORT 8808
#define BUFSIZE 1024
#define FILE_BUFSIZE 64


int main(void){

    struct sockaddr_in server;

    int sock;
    char buf[1024];

    char fname[256];
    char fname_with_path[256];
    char *token;
    long int n;

    int result;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    result = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if(result){
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("connected.\n");

    do{
        printf("> ");
        scanf("%s", fname_with_path);

        send_file(sock, fname_with_path);

    }while(strcmp(buf, "q"));

    close(sock);

    return 0;
}
