#include "interface.h"

#include <windows.h>
#include <string>
#include <iostream>

#include <boost/asio.hpp>

using namespace std;

void boost_return() {
	using namespace boost::asio;

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
	servAddr.sin_addr.s_addr = inet_addr(IP);
	servAddr.sin_port = htons(RESULTPORT);
	memset(servAddr.sin_zero, 0x00, 8);

	bytes = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));

	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(sockaddr_in));
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(REQUESTPORT);
	clientAddr.sin_addr.s_addr = inet_addr(IP);
	
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
		printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer);
	}

	closesocket(clientSoc);
	WSACleanup();
}