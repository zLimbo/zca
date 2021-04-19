#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const int BUF_SIZE = 1024;

int main() {
	
	int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1234);
	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	char fileName[100] = "../demoReq/certReq.pem";
	FILE *fp = fopen(fileName, "rb");
	if (fp == NULL) {
		printf("error");
		_exit(0);
	}
	char buffer[BUF_SIZE] = {0};
	int nCount = 0;
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		write(clientSocket, buffer, nCount);
	}
	shutdown(clientSocket, SHUT_WR); 

	fclose(fp);
	close(clientSocket);

	return 0;
}
