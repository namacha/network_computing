#ifndef HEADERS_H
#define HEADERS_H

unsigned char ACK[];
__attribute__((noreturn)) void panic(char* msg);

void acknowledge(int sock, char* msg);

#endif
