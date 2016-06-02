////#include "../TraceSimilarity/interface.h"
//#include <boost/asio.hpp>
//#include <windows.h>
//#include <string>
//#include <time.h>
//#include <vector>
//#include <boost/bind.hpp> 
//#include <iostream>
//#include "xNES.h"
//#pragma comment(lib, "WS2_32")	
//
//using namespace std;
//
////#define UNICODE
//
//#define RESULTPORT 15777
//#define REQUESTPORT 15777
//#define PARAMPORT 15778
//#define IP "127.0.0.1"
//#define MAX_BUFFER 8192
//
//using namespace boost::asio;
//
//char SendBuffer[MAX_BUFFER];
//char ReceiveBuffer[MAX_BUFFER];
//
//typedef std::function<void(struct Boost_Sock *, char *, size_t)> MSGHANDLER;
//boost::asio::io_service ioservice;
//ip::tcp::socket sock(ioservice);
//
//struct paramop_msg {
//	char op[256];
//	paramop_msg() {
//		memset(op, '\0', 256);
//	}
//};
//
//struct Boost_Sock {
//	boost::asio::ip::tcp::socket sock;
//	boost::asio::ip::tcp::endpoint ep;
//	std::string ip;
//	std::string name;
//	unsigned short port;
//	size_t max_buffer;
//	MSGHANDLER handler;
//	Boost_Sock(std::string ip, unsigned short port, MSGHANDLER msghandler = nullptr, std::string name = "") :ip(ip), port(port), sock(ioservice)
//		, ep(boost::asio::ip::address::from_string(ip), port), handler(msghandler), name(name) {
//	}
//	void send_str(const char * str, size_t len) {
//		using namespace boost::asio;
//		if (sock.send(buffer(str, len)) == SOCKET_ERROR)
//		{
//			cout << "Send Data Error::" << GetLastError() << endl;
//		}
//	}
//	void msg_loop() {
//		using namespace boost::asio;
//		try {
//			boost::system::error_code error;
//			sock.connect(ep, error);
//			if (error == boost::asio::error::connection_refused) {
//				cout << "No Remote Server At: " << this->name << endl;
//				return;
//			}
//		}
//		catch (...) {
//
//		}
//		int bytes = 0;
//		while (true)
//		{
//			//if ((bytes = sock.receive(buffer(ReceiveBuffer))) == SOCKET_ERROR)
//			//{
//			//	printf("recv error!\n"); exit(-1);
//			//}
//			boost::system::error_code error;
//			bytes = sock.read_some(buffer(ReceiveBuffer), error);
//			if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
//				sock.close();
//				return; // Connection closed cleanly by peer.
//			}
//			if (this->handler == nullptr) {
//				ReceiveBuffer[bytes] = '\0';
//				printf("%s\n", ReceiveBuffer);
//			}
//			else {
//				this->handler(this, ReceiveBuffer, bytes);
//			}
//			//char IPdotdec[20];inet_ntop(AF_INET, 0, IPdotdec, 16); printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer); //deprecated
//		}
//	}
//private:
//	char ReceiveBuffer[MAX_BUFFER];
//};
//
//void send_param_message(const paramop_msg & msg) {
//	int bytes = 0;
//	boost::system::error_code error;
//	//strncpy(SendBuffer, msg.c_str(), msg.size());
//	strncpy(SendBuffer, (char*)&msg, sizeof(msg));
//	if (sock.write_some(buffer(SendBuffer, sizeof(msg))) == SOCKET_ERROR)
//	{
//		cout << "Param Optimizer Error: " << GetLastError() << endl;
//	}
//	bytes = sock.read_some(buffer(ReceiveBuffer), error);
//	if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
//		sock.close();
//		return; // Connection closed cleanly by peer.
//	}
//	printf("Param Optimizer Finished: %s\n", ReceiveBuffer);
//}
//
//void init_param_server(int port = PARAMPORT) {
//	using namespace std;
//	ip::tcp::acceptor acceptor(ioservice, ip::tcp::endpoint(ip::tcp::v4(), PARAMPORT));
//	acceptor.accept(sock);
//	//int bytes = read(sock, buffer(ReceiveBuffer), boost::bind(send_param_message, ReceiveBuffer, _1, _2));
//	//std::string msg(buff, bytes);
//	//sock.write_some(buffer(msg));
//	return;
//}
//
//int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
//	//while (true) {
//	cout << "Listening" << endl;
//	init_param_server();
//	paramop_msg pm;
//	strcpy(pm.op, "rate, 0.55, 0.9");
//	send_param_message(pm);
//	cout << "Connection End" << endl;
//	//}
//	system("pause");
//	return 0;
//}
//
//
//void return_server() {
//	//	WSADATA wsaData;
//	//	// init Winsock.dll
//	//	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
//	//	{
//	//		printf("fail to init winsock.dll!\n");
//	//		exit(-1);
//	//	}
//	//	// creat socket
//	//	SOCKET servSoc;
//	//	// SOCK_STREAM is TCP
//	//	if ((servSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
//	//	{
//	//		printf("create socket error!\n");
//	//		exit(-1);
//	//	}
//	//
//	//	struct sockaddr_in servAddr;
//	//	memset(&servAddr, 0, sizeof(sockaddr_in));
//	//	servAddr.sin_family = AF_INET;
//	//	servAddr.sin_port = htons(RESULTPORT);
//	//	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	//
//	//	// bind addr
//	//	if (bind(servSoc, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
//	//	{
//	//		printf("bind error! port:%d\n", RESULTPORT);
//	//		exit(-1);
//	//	}
//	//	// max connection = 2
//	//	if (listen(servSoc, 2) == SOCKET_ERROR)
//	//	{
//	//		printf("listen error!\n");
//	//		exit(-1);
//	//	}
//	//	printf("Server %d is listening...\n", RESULTPORT);
//	//
//	//	SOCKET clientSoc;
//	//	struct sockaddr_in clientAddr;
//	//	memset(&clientAddr, 0, sizeof(clientAddr));
//	//	int addrlen = sizeof(clientAddr);
//	//	// accept
//	//	if ((clientSoc = accept(servSoc, (sockaddr*)&clientAddr, &addrlen)) == INVALID_SOCKET)
//	//	{
//	//		printf("accept error!\n");
//	//		exit(-1);
//	//	}
//	//	printf("Accept connection from %s\n", inet_ntoa(clientAddr.sin_addr));
//	//	char SendBuffer[] = "Message Received.";
//	//	char ReceiveBuffer[MAX_BUFFER];
//	//	while (1)
//	//	{
//	//		int bytes;
//	//		if ((bytes = recv(clientSoc, ReceiveBuffer, sizeof(ReceiveBuffer), 0)) == SOCKET_ERROR)
//	//		{
//	//			printf("recv error!\n");
//	//			exit(-1);
//	//		}
//	//		ReceiveBuffer[bytes] = '\0';
//	//		printf("Message from %s:%s\n", inet_ntoa(clientAddr.sin_addr), ReceiveBuffer);
//	//		if (send(clientSoc, SendBuffer, bytes, 0) == SOCKET_ERROR)
//	//		{
//	//			printf("send error!\n");
//	//			exit(-1);
//	//		}
//	//	}
//	//	// clean socket
//	//	WSACleanup();
//}