#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN 1000 //длина адреса

int main(int argc, char const *argv[]) {
	int sockfd;

	char sendline[LEN]; //строка отправлю, приму
	struct sockaddr_in servaddr, cliaddr;

	if (argc != 3) {
		fprintf(stderr, "Insert IP and Port!\n");
		exit(EXIT_FAILURE);
	}

	int port = *(int *)argv[2];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket!");
		exit(EXIT_FAILURE);
	}

	//client

	bzero(&cliaddr, sizeof(cliaddr));

	cliaddr.sin_family = AF_INET;
	// cliaddr.sin_port = 0;
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr*) &cliaddr, sizeof(cliaddr)) < 0) {
		perror("bind, client");
		close(sockfd);
		exit(EXIT_FAILURE);
	}


	// server

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);


	if (inet_aton(argv[1], &servaddr.sin_addr) == 0) {
		fprintf(stderr, "Invalid IP-address\n");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}

	printf("Insert string: ");
	fgets(sendline, LEN, stdin);
	write(sockfd, sendline, strlen(sendline));

	int i = 0, k = 1;
	char buf;
	char * temp = (char *)malloc(100 * sizeof(char));
	while (read(sockfd, &buf, 1) > 0) {
		if (i >= k * 100) {
			k++;
			temp = realloc(temp, k * 100 * sizeof(char));
		}
		temp[i] = buf;
		i++;
	}

	printf("Recieved: %s\n", temp);

	close(sockfd);

	return 0;
}