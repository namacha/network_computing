#include <stdio.h>

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



/*int main(){
    struct command ack = {ACK, "5.jpg", "/home/ics-01/ayu/a/img/5.jpg", 4974889};
    struct command received;
    unsigned char buffer[PACKET_LENGTH], *ptr;
    int i;
    bzero(buffer, sizeof(buffer));

    ptr = serialize_command(buffer, &ack);
    for(i=0;i<PACKET_LENGTH;i++)
        printf("%x ", buffer[i]);
    printf("\n");
    deserialize_command(ptr-PACKET_LENGTH, &received);
    printf("cmd = %x\n fname = %s\nfname_with_path = %s\nfsize = %lu\n", received.cmd, received.fname, received.fname_with_path, received.fsize);

    return 0;
}*/
