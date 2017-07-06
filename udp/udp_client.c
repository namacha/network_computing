#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>


int main(void){

    int sock;
    struct sockaddr_in addr;

    char buf[2048];
    char to_addr[32] = "127.0.0.1";
    int n;

    struct timeval time_old, time_new;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8809);
    addr.sin_addr.s_addr = inet_addr(to_addr);

    printf("Ready to send message to %s...\n", to_addr);

    while(1){
        printf("> ");
        scanf("%s", buf);

        gettimeofday(&time_old, NULL);

        sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));

        bzero(buf, sizeof(buf));  // make sure message is really received from peer.
        recv(sock, buf, sizeof(buf), 0);

        gettimeofday(&time_new, NULL);
        printf("RTT: %ld.%d[sec]\n", time_new.tv_sec - time_old.tv_sec, time_new.tv_usec - time_old.tv_usec);

        printf("%s\n", buf);

    }

    return 0;
}

