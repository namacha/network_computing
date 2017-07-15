#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

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

int acknowledge(int sock, char* msg){
    struct command decoded;
    char buf[PACKET_LENGTH];
    int n, result;

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    result = select(sock+1, &readfds, NULL, NULL, &tv);

    if(FD_ISSET(sock, &readfds)){
      n = read(sock, buf, PACKET_LENGTH);
      deserialize_command(&buf[0], &decoded);
      if(decoded.cmd != ACK){
          perror(msg);
          exit(EXIT_FAILURE);
      }
      return 0;
    }else{
        return 1;
    }
}
