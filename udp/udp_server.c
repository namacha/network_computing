#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void){

    int sock;
    struct sockaddr_in addr;
    struct sockaddr_in sender;

    socklen_t addrlen;
    int n;
    int yes = 1;

    char buf[2048];
    char sender_str[16];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8809);
    addr.sin_addr.s_addr = INADDR_ANY;

    setsockopt(
            sock,
            SOL_SOCKET,
            SO_REUSEADDR,
            (const char *)&yes,
            sizeof(yes)
            );

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    while(1){

        memset(buf, 0, sizeof(buf));
        addrlen = sizeof(sender);
        n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&sender, &addrlen);

        inet_ntop(AF_INET, &sender.sin_addr, sender_str, sizeof(sender_str));
        
        printf("%s", buf);
        printf("from %s:%d\n", sender_str, ntohs(sender.sin_port));

    }

    close(sock);

    return 0;
}
