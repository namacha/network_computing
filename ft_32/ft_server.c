#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "headers.h"
#include "packets.h"

#define PORT       8808
#define BUFSIZE    1024
#define FILE_BUFSIZE 64
#define MAXCLIENT  10


int main(int argc,char *argv[]){

    struct sockaddr_in saddr;
    struct sockaddr_in caddr;

    int sock;          // sever socket
    int client_sock;

    socklen_t len;

    int rsize;
    char buf[BUFSIZE];
    char fbuf[FILE_BUFSIZE];

    char fname[256];

    int pid, cpid;
    long int n;

    int yes = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
        panic("socket");

    saddr.sin_family      = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port        = htons(PORT);

    setsockopt(
            sock,
            SOL_SOCKET,
            SO_REUSEADDR,
            (const char *)&yes,
            sizeof(yes)
            );


    if (bind(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sock, MAXCLIENT) < 0)
        panic("listen");

    printf("Server established on PORT %d\n" , PORT);


    while(1){
        len = sizeof(caddr);

        client_sock = accept(sock, (struct sockaddr *)&caddr, &len);
        if (client_sock < 0)
            panic("accept");

        int client_port;
        client_port = ntohs(caddr.sin_port);

        printf("Connection accepted from: %s:%d\n", inet_ntoa(caddr.sin_addr), client_port);

        pid = fork();


        if (pid == 0){
            while(1){
                struct command decoded;

                receive_command(client_sock, &decoded);
                send_ack(client_sock);

                if(decoded.cmd == CLOSE){
                    close(client_sock);
                    printf("Disconnected\n");
                    break;
                }
                else if(decoded.cmd == SEND){
                    recv_file(client_sock);
                }
                else if(decoded.cmd == REQ){
                    send_file(client_sock, decoded.fname_with_path);
                }
             }
            }
        }
    close(sock);
    return 0;
}
