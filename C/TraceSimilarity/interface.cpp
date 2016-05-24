#include <WinSock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <chrono>
#include <functional>
#include <boost/asio.hpp>

using namespace std;
#pragma message("CPP")

#include "interface.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include "param.h"

struct paramop_msg {
	char op[6];
	paramop_msg() {
		memset(op, '\0', 6);
	}
};

void paramop_return() {
	using namespace boost::asio;
	io_service ioservice;
	ip::address addr = ip::address::from_string(IP);
	ip::tcp::endpoint ep(addr, PARAMPORT);
	ip::tcp::socket sock(ioservice);
	int bytes = 0;
	boost::system::error_code error;
	sock.connect(ep, error);
	if (error == boost::asio::error::connection_refused) {
		cout << "Leave Optimizer Mode!" << endl;
		return;
	}
	char SendBuffer[MAX_BUFFER];
	char ReceiveBuffer[MAX_BUFFER];
	paramop_msg * ppm;
	while (true)
	{
		//cin.getline(SendBuffer, sizeof(SendBuffer));
		//if (sock.write_some(buffer(SendBuffer)) == SOCKET_ERROR)
		//{
		//	cout << "Send Info Error::" << GetLastError() << endl;
		//	break;
		//}
		//bytes = sock.read_some(buffer(ReceiveBuffer), error);
		bytes = sock.read_some(buffer(ReceiveBuffer), error);
		if (error == boost::asio::error::eof)
			return; // Connection closed cleanly by peer.
		//char IPdotdec[20]; inet_ntop(AF_INET, 0, IPdotdec, 16); //inet_ntoa(clientAddr.sin_addr) is deprecated
		ppm = reinterpret_cast<paramop_msg*>(ReceiveBuffer);
		printf("%s\n", ppm->op);
	}
}

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

void file_return() {

}

char * result_encode(const TimeSimilarity & dat) {
	return NULL;
}
char * result_encode(const TimeSimilarityList & dat) {
	return NULL;
}
char * result_encode(const CoordSimilarity & dat) {
	return NULL;
}
char * result_encode(const CoordSimilarityList & dat) {
	return NULL;
}

template<typename _Func, typename... _Argv>
uint64_t elapse_time(_Func && f, _Argv&&... argv) {
	auto s = chrono::steady_clock::now();
	f(forward<_Argv>(argv)...);
	auto interval = chrono::steady_clock::now() - s;
	return static_cast<uint64_t>(chrono::duration_cast<chrono::milliseconds>(interval).count());
}


void return_by_socket() {
	//WSADATA  Ws;
	//SOCKET clientSoc;
	//struct sockaddr_in servAddr;
	//int bytes = 0;
	//char SendBuffer[MAX_BUFFER];
	//char ReceiveBuffer[MAX_BUFFER];

	////Init Windows Socket
	//if (WSAStartup(MAKEWORD(1, 1), &Ws) != 0)
	//{
	//	cout << "Init Windows Socket Failed::" << GetLastError() << endl;
	//	return;
	//}

	////Create Socket
	//clientSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if (clientSoc == INVALID_SOCKET)
	//{
	//	cout << "Create Socket Failed::" << GetLastError() << endl;
	//	return;
	//}

	//servAddr.sin_family = AF_INET;
	////servAddr.sin_addr.s_addr = inet_addr(IP); // deprecated
	//inet_pton(AF_INET, IP, (void *)&servAddr.sin_addr.s_addr);
	//servAddr.sin_port = htons(RESULTPORT);
	//memset(servAddr.sin_zero, 0x00, 8);

	//bytes = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));

	//struct sockaddr_in clientAddr;
	//memset(&clientAddr, 0, sizeof(sockaddr_in));
	//clientAddr.sin_family = AF_INET;
	//clientAddr.sin_port = htons(REQUESTPORT);
	////clientAddr.sin_addr.s_addr = inet_addr(IP); // deprecated
	//inet_pton(AF_INET, IP, (void *)&clientAddr.sin_addr.s_addr);
	//
	//if (bytes == SOCKET_ERROR)
	//{
	//	cout << "Connect Error::" << GetLastError() << endl;
	//	return;
	//}
	//else
	//{
	//	cout << "Connection Success!" << endl;
	//}

	//while (true)
	//{
	//	cin.getline(SendBuffer, sizeof(SendBuffer));

	//	if (send(clientSoc, SendBuffer, (int)strlen(SendBuffer), 0) == SOCKET_ERROR)
	//	{
	//		cout << "Send Info Error::" << GetLastError() << endl;
	//		break;
	//	}
	//	if ((bytes = recv(clientSoc, ReceiveBuffer, sizeof(ReceiveBuffer), 0)) == SOCKET_ERROR)
	//	{
	//		printf("recv error!\n");
	//		exit(-1);
	//	}
	//	ReceiveBuffer[bytes] = '\0';
	//	char IPdotdec[20];
	//	inet_ntop(AF_INET, (void *)&clientAddr.sin_addr, IPdotdec, 16);
	//	printf("Message from %s:%s\n", IPdotdec, ReceiveBuffer);
	//	// printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer); //deprecated
	//}

	//closesocket(clientSoc);
	//WSACleanup();
}

