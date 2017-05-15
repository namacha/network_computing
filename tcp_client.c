#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8808

int main(void){

    struct sockaddr_in server;

    int sock;
    char buf[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    write(sock, "hello", sizeof("hello"));
    memset(buf, 0, sizeof(buf));
    n = read(sock, buf, sizeof(buf));
    
    printf("%d, %s\n", n, buf);

    close(sock);

    return 0;
}
