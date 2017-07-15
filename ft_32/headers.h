#ifndef HEADERS_H
#define HEADERS_H

__attribute__((noreturn)) void panic(char* msg);

void send_ack(int sock);

void acknowledge(int sock, char* msg);

#endif
