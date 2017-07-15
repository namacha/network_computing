#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "packets.h"


unsigned char ACK = 0x13;
unsigned char REQ = 0x30;
unsigned char SEND = 0x49;
unsigned char CLOSE = 0x4f;


unsigned char * serialize_char(unsigned char *buffer, char value){
    buffer[0] = value;
    return buffer + 1;
}

unsigned char * serialize_int(unsigned char *buffer, int value){
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

unsigned char * serialize_str(unsigned char *buffer, char *value, int size){
    int i;
    for(i = 0;i < size; i++)
        buffer = serialize_char(buffer, value[i]);
    return buffer;
}

unsigned char * deserialize_char(unsigned char *buffer, unsigned char *dst){
    *dst = buffer[0];
    return ++buffer;
}

unsigned char * deserialize_str(unsigned char *buffer, char *dst, int size){
    int i;
    for(i=0; i<size; i++)
        buffer = deserialize_char(buffer++, &dst[i]);
    return buffer;
}

unsigned char * deserialize_int(unsigned char *buffer, int *dst){
    *dst = (buffer[0]<<24) + (buffer[1]<<16) + (buffer[2]<<8) + buffer[3];
    return buffer + 4;
}

unsigned char * serialize_command(unsigned char *buffer, struct command *value){
    buffer = serialize_char(buffer, value->cmd);
    buffer = serialize_str(buffer, value->fname, FNAME_LENGTH);
    buffer = serialize_str(buffer, value->fname_with_path, FNAME_LENGTH);
    buffer = serialize_int(buffer, value->fsize);
    return buffer;
}

void deserialize_command(unsigned char *buffer, struct command *value){
    unsigned char cmd;
    char fname[FNAME_LENGTH];
    char fname_with_path[FNAME_LENGTH];
    int fsize = 0;

    buffer = deserialize_char(buffer, &value->cmd);
    buffer = deserialize_str(buffer, value->fname, FNAME_LENGTH);
    buffer = deserialize_str(buffer, value->fname_with_path, FNAME_LENGTH);
    buffer = deserialize_int(buffer, &value->fsize);
}

void send_command(int sock, unsigned char cmd, char *fname, char *fname_with_path, int fsize){
    struct command value;
    unsigned char bytes[PACKET_LENGTH], *ptr;

    value.cmd = cmd;
    strcpy(value.fname, fname);
    strcpy(value.fname_with_path, fname_with_path);
    value.fsize = fsize;

    ptr = serialize_command(bytes, &value);

    write(sock, bytes, PACKET_LENGTH);
}


void receive_command(int sock, struct command *value){
    unsigned char bytes[PACKET_LENGTH];
    int n;

    n = read(sock, bytes, PACKET_LENGTH);
    deserialize_command(&bytes[0], value);
}
