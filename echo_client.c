#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {

    if(argc != 2){
      printf("Usage: %s <port>\n", argv[0]);
      exit(0);
    }

	printf("Jordano Iqbal Darmawan\n21120120130073\nUnix Network Programming\nEcho Client\n");

	int port = atoi(argv[1]);
	printf("Port: %d\n", port);

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	inet_aton("172.27.144.1", &server_addr.sin_addr);

	int sockfd;
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("couldn't create socket\n");
		return 1;
	}
	printf("socket created\n");

	if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
	printf("couldn't connect\n");
		return 1;
	}
	printf("connected to the server\n");

	char msg[100], server_msg[100];

	while (1) {
		printf("write message : ");
		scanf("%[^\n]%*c", msg);
		send(sockfd, msg, sizeof(msg), 0);

		memset(server_msg, 0, sizeof(server_msg));
		recv(sockfd, server_msg, sizeof(server_msg) , 0);
		printf("Server reply : %s\n", server_msg);

		if (strcmp(server_msg, "bye") == 0) {
			printf("exiting...\n");
			break;
		}
	}

	close(sockfd);

	return 0;
}