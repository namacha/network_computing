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

#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8808
#define BUFSIZE 1024
#define FILE_BUFSIZE 64

__attribute__((noreturn)) static void panic(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void){

    struct sockaddr_in server;

    char ACK[1] = ".";

    int sock;
    char buf[1024];

    char fname[256];
    char fname_with_path[256];
    char *token;
    int n;

    int result;

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
        scanf("%s", fname_with_path);

        int fd = open(fname_with_path, O_RDONLY);

        token = strtok(fname_with_path, "/");
        if(token != NULL){
          while(token != NULL){
              strcpy(buf, token);
              token = strtok(NULL, "/");
          }
          strcpy(fname, buf);
        }else{
            strcpy(fname, fname_with_path);
        }

        printf("%s\n", fname);

        write(sock, fname, sizeof(fname));

        n = read(sock, buf, sizeof(buf));
        if(!strcmp(buf, ACK))
            panic("ACK: fname");


        long long int sent_bytes = 0;
        off_t fsize = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        char fsize_c[256];

        printf("fsize: %lld\n", (long long int)fsize);

        sprintf(fsize_c, "%d", (int)fsize);

        write(sock, fsize_c, sizeof(fsize_c));

        n = read(sock, buf, sizeof(buf));
        if(!strcmp(buf, ACK))
            panic("ACK: fsize");

        while(sent_bytes < (long long int)fsize){
            if((long long int)fsize - sent_bytes > FILE_BUFSIZE){
                n = read(fd, buf, FILE_BUFSIZE);
                write(sock, buf, n);
                lseek(fd, FILE_BUFSIZE, SEEK_CUR);
            }else{
                n = read(fd, buf, FILE_BUFSIZE);
                write(sock, buf, n);
                lseek(fd, n, SEEK_CUR);
            }
            sent_bytes += n;
            printf("%lld\r", sent_bytes);
        }

        n = read(sock, buf, sizeof(buf));
        if(!strcmp(buf, ACK))
            panic("ACK: sent");

        printf("File sent.\n");
        close(fd);

    }while(strcmp(buf, "q"));

    close(sock);

    return 0;
}
