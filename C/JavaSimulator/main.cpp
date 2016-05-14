#include <windows.h>
#include <string>
#include <time.h>
#include <vector>

#pragma comment(lib, "WS2_32")	

using namespace std;

//#define UNICODE

#define RESULTPORT 15777
#define REQUESTPORT 15777
#define IP "127.0.0.1"
#define MAX_BUFFER 2048

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	WSADATA wsaData;
	// init Winsock.dll
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		printf("fail to init winsock.dll!\n");
		exit(-1);
	}
	// creat socket
	SOCKET servSoc;
	// SOCK_STREAM is TCP
	if ((servSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("create socket error!\n");
		exit(-1);
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(sockaddr_in));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(RESULTPORT);
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// bind addr
	if (bind(servSoc, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		printf("bind error! port:%d\n", RESULTPORT);
		exit(-1);
	}
	// max connection = 2
	if (listen(servSoc, 2) == SOCKET_ERROR)
	{
		printf("listen error!\n");
		exit(-1);
	}
	printf("Server %d is listening...\n", RESULTPORT);

	SOCKET clientSoc;
	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));
	int addrlen = sizeof(clientAddr);
	// accept
	if ((clientSoc = accept(servSoc, (sockaddr*)&clientAddr, &addrlen)) == INVALID_SOCKET)
	{
		printf("accept error!\n");
		exit(-1);
	}
	printf("Accept connection from %s\n", inet_ntoa(clientAddr.sin_addr));
	char SendBuffer[] = "HHHHHHHHH";
	char ReceiveBuffer[MAX_BUFFER];
	while (1)
	{
		int bytes;
		if ((bytes = recv(clientSoc, ReceiveBuffer, sizeof(ReceiveBuffer), 0)) == SOCKET_ERROR)
		{
			printf("recv error!\n");
			exit(-1);
		}
		ReceiveBuffer[bytes] = '\0';
		printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer);
		if (send(clientSoc, SendBuffer, bytes, 0) == SOCKET_ERROR)
		{
			printf("send error!\n");
			exit(-1);
		}
	}
	// clean socket
	WSACleanup();
	system("pause");
	return 0;
}