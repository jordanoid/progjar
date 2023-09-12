#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>

int sockfd, n = 0;
struct sockaddr_in serverAddress;
char recvline[1001];

int main(int argc, char **argv){
    if(argc != 2){
      printf("Usage: %s <port>\n", argv[0]);
      exit(0);
    }

    printf("Jordano Iqbal Darmawan\n21120120130073\nUnix Network Programming\n");
    int port = atoi(argv[1]);
    printf("Port: %d\n", port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
	inet_aton("172.27.144.1", &serverAddress.sin_addr);

    connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    printf("[+]Connected to the server\n");


    while ((n = read(sockfd, recvline, 1000)) > 0) {
        recvline[n] = 0;
        fputs(recvline, stdout);
    }

    return 0;

}