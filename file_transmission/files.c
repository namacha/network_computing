#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "headers.h"

#define FILE_BUFSIZE 64


int send_file(int sock, char* fname_with_path){
    char buf[1024];
    char fname[256];
    char* token;
    int fd = open(fname_with_path, O_RDONLY);
    int n;

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

    printf("fname: %s\n", fname);

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
    close(fd);

    printf("File sent.\n");

    return bytes_to_send;
}
