#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "headers.h"
#include "packets.h"


__attribute__((noreturn)) void panic(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


void send_ack(int sock){
    struct command ack;
    char bytes[PACKET_LENGTH], *ptr;

    ack.cmd = ACK;
    ptr = serialize_command(bytes, &ack);
    write(sock, bytes, PACKET_LENGTH);
}

void acknowledge(int sock, char* msg){
    struct command decoded;
    char buf[PACKET_LENGTH];
    int n;
    n = read(sock, buf, PACKET_LENGTH);
    deserialize_command(&buf[0], &decoded);
    if(decoded.cmd != ACK){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}
