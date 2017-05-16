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
    int n;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8809);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1){

        scanf("%s", buf);

        sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));

        //memset(buf, 0, sizeof(buf));
        bzero(buf, sizeof(buf));

//        recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
        recv(sock, buf, sizeof(buf), 0);

        printf("%s\n", buf);

    }

    return 0;
}

