#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include <string.h>

#define BACKLOG 10

int listenfd, connfd;
struct sockaddr_in serverAddress;
time_t ticks;
char buff[1024];


int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    printf("Jordano Iqbal Darmawan\n21120120130073\nUnix Network Programming\n");
    int port = atoi(argv[1]);
    printf("Port: %d\n", port);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    bind(listenfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    printf("[+]Bind\n");

    listen(listenfd, BACKLOG);
    printf("[+]Listening for the client\n");

    int i = 1;
    for (;;) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
    return 0;
}