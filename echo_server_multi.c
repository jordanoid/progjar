#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {

    if(argc != 2){
      printf("Usage: %s <port>\n", argv[0]);
      exit(0);
    }

	printf("Jordano Iqbal Darmawan\n21120120130073\nUnix Network Programming\nEcho Server\n");
	
    int port = atoi(argv[1]);
    printf("Port: %d\n", port);

	struct sockaddr_in server_addr;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
  	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
	int sockfd;
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("couldn't create socket\n");
		return 1;
	}
	printf("socket created\n");

	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		printf("couldn't bind socket\n");
		return 1;
	}
	printf("bind at port %d \n", port);
        
	if (listen(sockfd, 5) < 0) {
		printf("couldn't listen to socket\n");
		return 1;
	}
	printf("listening connection: 5\n");

	struct sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);

	while (1) {
		int client_sockfd;
		if ((client_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_size)) < 0) {
			printf("couldn't accept connection\n");
			return 1;
		}
		printf("accepted connection from %s\n", inet_ntoa(client_addr.sin_addr));

		char msg[100];
        if(fork() == 0){
            while(1) {
                recv(client_sockfd, msg, sizeof(msg), 0);
                printf("msg recv = %s\n", msg);

                send(client_sockfd, msg, sizeof(msg), 0);

                if (strcmp(msg, "bye") == 0) {
                    printf("exiting...\n");
                    break;
                }
		    }
        }
		
        
		close(client_sockfd);
	}

	close(sockfd);

	return 0;
}