#include <WinSock2.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp> 
#include <iostream>

#include "xNES.h"

#pragma comment(lib, "WS2_32")	

using namespace std;

//#define UNICODE

#define RESULTPORT 15777
#define REQUESTPORT 15777
#define PARAMPORT 15778
#define IP "127.0.0.1"
#define MAX_BUFFER 2048

using namespace boost::asio;

char SendBuffer[MAX_BUFFER];
char ReceiveBuffer[MAX_BUFFER];
io_service ioservice;
ip::tcp::acceptor acceptor(ioservice, ip::tcp::endpoint(ip::tcp::v4(), PARAMPORT));
ip::tcp::socket sock(ioservice);

void send_param_message(string msg) {
	int bytes = 0;

	//strncpy(SendBuffer, msg.c_str(), msg.size());
	if (sock.write_some(buffer(msg)) == SOCKET_ERROR)
	{
		cout << "Send Info Error::" << GetLastError() << endl;
	}
	if ((bytes = read(sock, buffer(ReceiveBuffer))) == SOCKET_ERROR)
	{
		printf("recv error!\n");
		return;
	}
	//char IPdotdec[20]; inet_ntop(AF_INET, 0, IPdotdec, 16); //inet_ntoa(clientAddr.sin_addr) is deprecated
	printf("%s\n", ReceiveBuffer);
}

void init_param_server(int port = PARAMPORT) {
	using namespace std;
	acceptor.accept(sock);
	//int bytes = read(sock, buffer(ReceiveBuffer), boost::bind(send_param_message, ReceiveBuffer, _1, _2));
	//std::string msg(buff, bytes);
	//sock.write_some(buffer(msg));
	return ;
}


int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	init_param_server();
	send_param_message("C");
	system("pause");
	return 0;
}


void return_server() {
	//	WSADATA wsaData;
	//	// init Winsock.dll
	//	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	//	{
	//		printf("fail to init winsock.dll!\n");
	//		exit(-1);
	//	}
	//	// creat socket
	//	SOCKET servSoc;
	//	// SOCK_STREAM is TCP
	//	if ((servSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	//	{
	//		printf("create socket error!\n");
	//		exit(-1);
	//	}
	//
	//	struct sockaddr_in servAddr;
	//	memset(&servAddr, 0, sizeof(sockaddr_in));
	//	servAddr.sin_family = AF_INET;
	//	servAddr.sin_port = htons(RESULTPORT);
	//	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//
	//	// bind addr
	//	if (bind(servSoc, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	//	{
	//		printf("bind error! port:%d\n", RESULTPORT);
	//		exit(-1);
	//	}
	//	// max connection = 2
	//	if (listen(servSoc, 2) == SOCKET_ERROR)
	//	{
	//		printf("listen error!\n");
	//		exit(-1);
	//	}
	//	printf("Server %d is listening...\n", RESULTPORT);
	//
	//	SOCKET clientSoc;
	//	struct sockaddr_in clientAddr;
	//	memset(&clientAddr, 0, sizeof(clientAddr));
	//	int addrlen = sizeof(clientAddr);
	//	// accept
	//	if ((clientSoc = accept(servSoc, (sockaddr*)&clientAddr, &addrlen)) == INVALID_SOCKET)
	//	{
	//		printf("accept error!\n");
	//		exit(-1);
	//	}
	//	printf("Accept connection from %s\n", inet_ntoa(clientAddr.sin_addr));
	//	char SendBuffer[] = "Message Received.";
	//	char ReceiveBuffer[MAX_BUFFER];
	//	while (1)
	//	{
	//		int bytes;
	//		if ((bytes = recv(clientSoc, ReceiveBuffer, sizeof(ReceiveBuffer), 0)) == SOCKET_ERROR)
	//		{
	//			printf("recv error!\n");
	//			exit(-1);
	//		}
	//		ReceiveBuffer[bytes] = '\0';
	//		printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer);
	//		if (send(clientSoc, SendBuffer, bytes, 0) == SOCKET_ERROR)
	//		{
	//			printf("send error!\n");
	//			exit(-1);
	//		}
	//	}
	//	// clean socket
	//	WSACleanup();
}