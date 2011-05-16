#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#define TEST_PORT 9090
#define TEST_IP "255.255.255.255"

int main(int argc, char *argv[]) {
	struct sockaddr_in addr1, addr2;
	int fd1, fd2;

	if ((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	if ((fd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	int broadcastOpt = 1;
	if (0 != setsockopt(fd2, SOL_SOCKET, SO_BROADCAST, &broadcastOpt, sizeof(broadcastOpt))) {
		perror("setsockopt");
		exit(1);
	}

	memset(&addr1, 0, sizeof(addr1));
	addr1.sin_family = AF_INET;
	addr1.sin_addr.s_addr = htonl(INADDR_ANY);
	addr1.sin_port = htons(TEST_PORT);

	memset(&addr2, 0, sizeof(addr2));
	addr2.sin_family = AF_INET;
	addr2.sin_port = htons(TEST_PORT);
	addr2.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	if (0 != bind(fd1, (struct sockaddr*) &addr1, sizeof(addr1))) {
		perror("bind");
		exit(1);
	}

	const char message1[24] = "HELLO";
	if (-1 == sendto(fd2, message1, sizeof(message1), 0, (struct sockaddr*) &addr2, sizeof(addr2))) {
		perror("sendto");
		exit(1);
	}

	char message2[24];
	unsigned int message2len;
	if (-1 == recvfrom(fd1, message2, sizeof(message2), 0, (struct sockaddr*) &addr1, &message2len)) {
		perror("recvfrom");
		exit(1);
	}

	fprintf(stdout, "%s\n", message2);

	return 0;
}
