#include <WinSock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <boost/asio.hpp>

using namespace std;
#pragma message("CPP")

#include "interface.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"

void boost_return() {
	using namespace boost::asio;
	io_service ioservice;
	ip::address addr = ip::address::from_string(IP);
	ip::tcp::endpoint ep(addr, RESULTPORT);
	ip::tcp::socket sock(ioservice);
	sock.connect(ep);
	int bytes = 0;
	char SendBuffer[MAX_BUFFER];
	char ReceiveBuffer[MAX_BUFFER];

	while (true)
	{
		cin.getline(SendBuffer, sizeof(SendBuffer));
		if (sock.send(buffer(SendBuffer)) == SOCKET_ERROR)
		{
			cout << "Send Info Error::" << GetLastError() << endl;
			break;
		}
		if ((bytes = sock.receive(buffer(ReceiveBuffer))) == SOCKET_ERROR)
		{
			printf("recv error!\n");
			exit(-1);
		}
		ReceiveBuffer[bytes] = '\0';
		char IPdotdec[20];
		inet_ntop(AF_INET,0, IPdotdec, 16);
		printf("Message from %s:%s\n", IPdotdec, ReceiveBuffer);
		// printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer); //deprecated
	}
}

void return_by_socket() {
	WSADATA  Ws;
	SOCKET clientSoc;
	struct sockaddr_in servAddr;
	int bytes = 0;
	char SendBuffer[MAX_BUFFER];
	char ReceiveBuffer[MAX_BUFFER];

	//Init Windows Socket
	if (WSAStartup(MAKEWORD(1, 1), &Ws) != 0)
	{
		cout << "Init Windows Socket Failed::" << GetLastError() << endl;
		return;
	}

	//Create Socket
	clientSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSoc == INVALID_SOCKET)
	{
		cout << "Create Socket Failed::" << GetLastError() << endl;
		return;
	}

	servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr(IP); // deprecated
	inet_pton(AF_INET, IP, (void *)&servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(RESULTPORT);
	memset(servAddr.sin_zero, 0x00, 8);

	bytes = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));

	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(sockaddr_in));
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(REQUESTPORT);
	//clientAddr.sin_addr.s_addr = inet_addr(IP); // deprecated
	inet_pton(AF_INET, IP, (void *)&clientAddr.sin_addr.s_addr);
	
	if (bytes == SOCKET_ERROR)
	{
		cout << "Connect Error::" << GetLastError() << endl;
		return;
	}
	else
	{
		cout << "Connection Success!" << endl;
	}

	while (true)
	{
		cin.getline(SendBuffer, sizeof(SendBuffer));

		if (send(clientSoc, SendBuffer, (int)strlen(SendBuffer), 0) == SOCKET_ERROR)
		{
			cout << "Send Info Error::" << GetLastError() << endl;
			break;
		}
		if ((bytes = recv(clientSoc, ReceiveBuffer, sizeof(ReceiveBuffer), 0)) == SOCKET_ERROR)
		{
			printf("recv error!\n");
			exit(-1);
		}
		ReceiveBuffer[bytes] = '\0';
		char IPdotdec[20];
		inet_ntop(AF_INET, (void *)&clientAddr.sin_addr, IPdotdec, 16);
		printf("Message from %s:%s\n", IPdotdec, ReceiveBuffer);
		// printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer); //deprecated
	}

	closesocket(clientSoc);
	WSACleanup();
}

void file_return() {

}

char * result_encode(TimeSimilarity dat) {
	return NULL;
}
char * result_encode(TimeSimilarityList dat) {
	return NULL;
}
char * result_encode(CoordSimilarity dat) {
	return NULL;
}
char * result_encode(CoordSimilarityList dat) {
	return NULL;
}

void fuckme() {
	cout << "fuckme" << endl;
}