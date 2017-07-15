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
#include <libgen.h>

#include "headers.h"
#include "packets.h"


#define FILE_BUFSIZE 64


void extract_basename(char *filename_with_path, char *dst){   //set filename to dst 
    // fix later
    strcpy(dst, basename(filename_with_path));
}


int send_file(int sock, char* fname_with_path){
    char fname[FNAME_LENGTH];
    char buf[1024];
    int fd = open(fname_with_path, O_RDONLY);
    int n;

    off_t fsize = lseek(fd, 0, SEEK_END);
    unsigned long int bytes_to_send = (unsigned long int)fsize;
    lseek(fd, 0, SEEK_SET);

    extract_basename(fname_with_path, fname);

    printf("sending %s(%llu)\n", fname_with_path, fsize);
    send_command(sock, SEND, fname, fname_with_path, fsize);
    acknowledge(sock, "after send cmd");


    while(bytes_to_send){
        if(bytes_to_send >= FILE_BUFSIZE){
            n = read(fd, buf, FILE_BUFSIZE);
            write(sock, buf, n);
        }else{
            n = read(fd, buf, bytes_to_send);
            write(sock, buf, n);
        }
        bytes_to_send -= n;
        printf("%llu\r", fsize-bytes_to_send);
    }

    close(fd);
    printf("\n...Completed.\n");
    return bytes_to_send;
}

int recv_file(int sock){
    struct command value;
    int n;
    char buf[64];

    receive_command(sock, &value);
    send_ack(sock);

    printf("receiving %s(%lu)", value.fname, value.fsize);


    int fd = open(value.fname, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP);
    long int bytes_to_receive = value.fsize;
    while(bytes_to_receive){
        n = read(sock, buf, sizeof(buf));
        if (n < 0)
            panic("read");
        write(fd, buf, n);
        bytes_to_receive -= n;
    }

    close(fd);
    printf("...Completed.\n");
    return bytes_to_receive;
}
