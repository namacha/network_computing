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


#define FILE_BUFSIZE 4096
#define DESTROY_RATE 0.2


void extract_basename(char *filename_with_path, char *dst){   //set filename to dst 
    // fix later
    strcpy(dst, basename(filename_with_path));
}


int send_file(int sock, char* fname_with_path){
    char fname[FNAME_LENGTH];
    char buf[FILE_BUFSIZE];
    int fd = open(fname_with_path, O_RDONLY);
    int resend = 0;
    int n, has_timeout = 0;

    off_t fsize = lseek(fd, 0, SEEK_END);
    unsigned long int bytes_to_send = (unsigned long int)fsize;
    lseek(fd, 0, SEEK_SET);

    extract_basename(fname_with_path, fname);

    send_command(sock, SEND, fname, fname_with_path, fsize);
    n = acknowledge(sock, "after send cmd");
    printf("sending %s(%llu)\n", fname_with_path, fsize);

    while(bytes_to_send){
        if(bytes_to_send >= FILE_BUFSIZE){
            if(!resend)
              n = read(fd, buf, FILE_BUFSIZE);
            write(sock, buf, n);
            has_timeout = acknowledge(sock, "receive file buffer");
        }else{
            if(!resend)
              n = read(fd, buf, bytes_to_send);
            write(sock, buf, n);
            has_timeout = acknowledge(sock, "receive file buffer");
        }

        printf("%llu\r", fsize-bytes_to_send);
        if(has_timeout == 0){
          bytes_to_send -= n;
          resend = 0;
        }else{
            printf("TIMEOUT!\n");
            has_timeout = 0;
            resend = 1;
        }
    }

    close(fd);
    printf("\n...Completed.\n");
    return bytes_to_send;
}

int recv_file(int sock){
    struct command value;
    int n;
    char buf[FILE_BUFSIZE];

    receive_command(sock, &value);
    send_ack(sock);

    srand(value.fsize);  // seed for random

    printf("receiving %s(%lu)\n", value.fname, value.fsize);


    int fd = open(value.fname, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP);
    long int bytes_to_receive = value.fsize;
    float p;

    while(bytes_to_receive){
        n = read(sock, buf, sizeof(buf));
        p = (float)rand() / RAND_MAX;
        if (n < 0)
            panic("read");
        if(p < DESTROY_RATE){
            printf("(%f)DESTROYED PACKETS...\n", p);
        }else{
          write(fd, buf, n);
          send_ack(sock);
          bytes_to_receive -= n;
        }
    }

    close(fd);
    printf("...Completed.\n");
    return bytes_to_receive;
}
