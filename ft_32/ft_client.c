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

#include "headers.h"
#include "files.h"
#include "packets.h"

#define PORT 8808
#define BUFSIZE 1024
#define FILE_BUFSIZE 64


int main(void){

    struct sockaddr_in server;

    int sock;
    char buf[1024];

    char fname[256];
    char fname_with_path[256];
    char *token;
    long int n;

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
    printf("Usage\n");
    printf("upload: upload file to server.\n");
    printf("download: download file from server.\n");
    printf("quit: disconnect from server and quit.\n");

    while(1){
        char user_command[32];
        char user_filename[FNAME_LENGTH];  // with full path

        printf("> ");
        scanf("%s", user_command);

        if(!strcmp(user_command, "quit")){
            printf("Bye.\n");
            exit(0);
        }

        printf("Enter filename with full path.\n> ");
        scanf("%s", user_filename);

        if(!strcmp(user_command, "upload"))
            send_file(sock, user_filename);
    }


    close(sock);

    return 0;
}
