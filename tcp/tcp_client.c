#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>


#define PORT 8808

int main(void){

    struct sockaddr_in server;

    int sock;
    char buf[1024];
    int n;

    int result;

    struct timeval time_o, time_n;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    result = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if(result){
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("connected.\n");

    do{
        printf("> ");
        scanf("%s", buf);

        gettimeofday(&time_o, NULL);

        write(sock, buf, sizeof(buf));
        memset(buf, 0, sizeof(buf));
        n = read(sock, buf, sizeof(buf));

        gettimeofday(&time_n, NULL);

        printf("RTT: %ld.%d[sec]\n", time_n.tv_sec - time_o.tv_sec, time_n.tv_usec - time_o.tv_usec);

        printf("%d, %s\n", n, buf);
    }while(strcmp(buf, "q"));

    close(sock);

    return 0;
}
