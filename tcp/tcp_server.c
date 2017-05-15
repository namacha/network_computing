#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT       8808
#define BUFSIZE    1024
#define MAXCLIENT  10


void panic(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


int main(void){

    struct sockaddr_in saddr;
    struct sockaddr_in caddr;

    int sock;          // sever socket
    int client_sock;

    socklen_t len;

    int rsize;
    char buf[BUFSIZE];

    int pid, cpid;
    int n;

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

        printf("Connection accepted from: %s:%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

        pid = fork();

        if (pid == 0){
            while(1){
              n = read(client_sock, buf, sizeof(buf));
              if (n < 0)
                  panic("read");
            
              write(client_sock, buf, n);
              }
            }
        }
    close(sock);
    return 0;
}
