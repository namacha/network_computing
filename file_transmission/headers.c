#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "headers.h"


unsigned char ACK[] = {0xff};

__attribute__((noreturn)) static void panic(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void acknowledge(int sock, char* msg){
    char buf[32];
    int n;
    n = read(sock, buf, 1);
    buf[1] = '\0';
    if(strcmp(buf, ACK)){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}
