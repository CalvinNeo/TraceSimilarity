#include "interface.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include "param.h"

#include <string>
#include <iostream>
#include <chrono>
#include <functional>
using namespace std;
#pragma message("CPP")

boost::asio::io_service ioservice;

void Sync_Sock::msg_loop() {
	using namespace boost::asio;
	try {
		boost::system::error_code error;
		sock.connect(ep, error);
		if (error == boost::asio::error::connection_refused) {
			cout << "No Remote Server At: " << this->name << endl;
			return;
		}
	}
	catch(...){

	}
	int bytes = 0;
	while (true)
	{
		//if ((bytes = sock.receive(buffer(ReceiveBuffer))) == SOCKET_ERROR)
		//{
		//	printf("recv error!\n"); exit(-1);
		//}
		boost::system::error_code error;
		bytes = sock.read_some(buffer(ReceiveBuffer), error);
		if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
			sock.close();
			return; // Connection closed cleanly by peer.
		}
		if (this->handler == nullptr) {
			ReceiveBuffer[bytes] = '\0';
			printf("%s\n", ReceiveBuffer);
		}
		else {
			this->handler(this, ReceiveBuffer, bytes);
		}
		//char IPdotdec[20];inet_ntop(AF_INET, 0, IPdotdec, 16); printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer); //deprecated
	}
}

void Sync_Sock::send_str(const char * str, size_t len) {
	using namespace boost::asio;
	boost::system::error_code error;
	sock.send(buffer(str, len), 0, error);
	if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
		cout << "Send Data Error::" << GetLastError() << endl;
		sock.close();
		return; // Connection closed cleanly by peer.
	}
}

void Sync_Server::init() {
	using namespace boost::asio;
	ip::tcp::acceptor acceptor(ioservice, ip::tcp::endpoint(ip::tcp::v4(), port));
	acceptor.accept(sock);
	//int bytes = read(sock, buffer(ReceiveBuffer), boost::bind(send_param_message, ReceiveBuffer, _1, _2));
	//std::string msg(buff, bytes);
	//sock.write_some(buffer(msg));
}

void Async_Sock::msg_loop() {
	using namespace boost::asio;
	try {
		boost::system::error_code error;
		sock.async_connect(ep, [this](const boost::system::error_code &error) {
			if (error == boost::asio::error::connection_refused) {
				cout << "No Remote Server At: " << this->name << endl;
				return;
			}
		});
	}
	catch (...) {

	}
	sock.async_read_some(buffer(ReceiveBuffer), [this](const boost::system::error_code &error, std::size_t bytes) {
		if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
			sock.close();
			return; // Connection closed cleanly by peer.
		}
		if (this->handler == nullptr) {
			ReceiveBuffer[bytes] = '\0';
			printf("%s\n", ReceiveBuffer);
		}
		else {
			this->handler(this, ReceiveBuffer, bytes);
		}
	});
}

void Async_Sock::send_str(const char * str, size_t len) {
	using namespace boost::asio;
	boost::system::error_code error;
	sock.send(buffer(str, len), 0, error);
	if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
		cout << "Send Data Error::" << GetLastError() << endl;
		sock.close();
		return; // Connection closed cleanly by peer.
	}
}

void Async_Server::init() {
	using namespace boost::asio;
	ip::tcp::acceptor acceptor(ioservice, ip::tcp::endpoint(ip::tcp::v4(), port));
	acceptor.accept(sock);
	//acceptor.async_accept(sock, [](const boost::system::error_code &error) {});
}





//void return_by_socket() {
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
//}

