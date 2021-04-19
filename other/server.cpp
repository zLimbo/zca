#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


const int BUF_SIZE = 1024;

int main() {
	
	int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1234);
	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	listen(serverSocket, 20);

	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

	char fileName[100] = "certReq.pem";
	FILE *fp = fopen(fileName, "wb");
	if (fp == NULL) {
		printf("error");
		_exit(0);
	}

	char buffer[BUF_SIZE] = {0};
	int nCount = 0;
	while ((nCount = read(clientSocket, buffer, BUF_SIZE)) > 0) {
		fwrite(buffer, nCount, 1, fp);
	}
	puts("File accept success!");

	fclose(fp);
	close(clientSocket);
	close(serverSocket);

	return 0;
}
