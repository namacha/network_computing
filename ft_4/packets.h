#ifndef PACKETS_H 
#define PACKETS_H

#define PACKET_LENGTH 261
#define FNAME_LENGTH 128

struct command {
    unsigned char cmd;
    char fname[FNAME_LENGTH];
    char fname_with_path[FNAME_LENGTH];
    unsigned long int fsize;
};

extern unsigned char ACK;
extern unsigned char REQ;
extern unsigned char SEND;
extern unsigned char CLOSE;

unsigned char * serialize_char(unsigned char *buffer, char value);
unsigned char * serialize_int(unsigned char *buffer, int value);
 unsigned char * serialize_str(unsigned char *buffer, char *value, int size);

unsigned char * deserialize_char(unsigned char *buffer, unsigned char *dst);
unsigned char * deserialize_str(unsigned char *buffer, char *dst, int size);
unsigned char * deserialize_int(unsigned char *buffer, int *dst);

unsigned char * serialize_command(unsigned char *buffer, struct command *value);
void deserialize_command(unsigned char *buffer, struct command *value);

void send_packet(int sock, unsigned char cmd, char *fname, char *fname_with_path, int fsize);
void receive_command(int sock, struct command *value);
     
#endif
