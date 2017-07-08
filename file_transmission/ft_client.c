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

        int fd = open(fname_with_path, O_RDONLY);

        token = strtok(fname_with_path, "/");
        if(token != NULL){
          while(token != NULL){
              strcpy(buf, token);
              token = strtok(NULL, "/");
          }
          strcpy(fname, buf);
        }else{
            strcpy(fname, fname_with_path);
        }

        printf("%s\n", fname);

        write(sock, fname, sizeof(fname));

        acknowledge(sock, "ACK: fname");

        off_t fsize = lseek(fd, 0, SEEK_END);
        long int bytes_to_send = (long int)fsize;
        lseek(fd, 0, SEEK_SET);

        char fsize_c[256];
        printf("fsize: %ld\n", (long int)fsize);
        sprintf(fsize_c, "%d", (int)fsize);
        write(sock, fsize_c, sizeof(fsize_c));

        acknowledge(sock, "ACK: fsize");

        while(bytes_to_send){
            if(bytes_to_send >= FILE_BUFSIZE){
                n = read(fd, buf, FILE_BUFSIZE);
                write(sock, buf, n);
            }else{
                n = read(fd, buf, bytes_to_send);
                write(sock, buf, n);
            }
            bytes_to_send -= n;
            printf("%ld\r", (long int)fsize-bytes_to_send);
        }

        acknowledge(sock, "ACK: sent");

        printf("File sent.\n");
        close(fd);

    }while(strcmp(buf, "q"));

    close(sock);

    return 0;
}
