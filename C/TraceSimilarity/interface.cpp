#include "interface.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include "param.h"

#include <string>
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
using namespace std;
#pragma message("CPP")

boost::asio::io_service ioservice;

void Sync_Sock::init() {
	using namespace boost::asio;
	try {
		boost::system::error_code error;
		sock.connect(ep, error);
		if (error == boost::asio::error::connection_refused) {
			cout << "No Remote Server At: " << this->name << endl;
			return;
		}
	}
	catch (...) {

	}
	msg_loop();
}
void Sync_Sock::async_init() {
	using namespace boost::asio;
	sock.async_connect(ep, [this](const boost::system::error_code &) -> void {
		this->msg_loop(); 
	});
	ios_thread = std::thread(
		[this]() {
		ioservice.run();
	});
}
void Sync_Sock::msg_loop() {
	using namespace boost::asio;
	while (true)
	{
		boost::system::error_code error;
		int bytes = sock.read_some(buffer(ReceiveBuffer), error);
		if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
			sock.close(); // close do not send fin
			return; // Connection closed cleanly by peer.
		}
		if (this->handler == nullptr) {
			ReceiveBuffer[bytes] = '\0';
			printf("%s\n", ReceiveBuffer);
		}
		else {
			if (this->handler(this, ReceiveBuffer, bytes) == true)
				return;
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
	acceptor.accept(sock);
	//int bytes = read(sock, buffer(ReceiveBuffer), boost::bind(send_param_message, ReceiveBuffer, _1, _2));
	//std::string msg(buff, bytes);
	//sock.write_some(buffer(msg));
}

void Sync_Server::async_init(std::function<void(const boost::system::error_code &)> handle) {
	using namespace boost::asio;
	acceptor.async_accept(sock, [=](const boost::system::error_code & x) -> void {
		handle(x);
		this->msg_loop();
	});
	//acceptor.async_accept(sock, handle);
	ios_thread = std::thread(
		[&]() {
		ioservice.run();
	});
}

void Async_Sock::msg_loop() {
	using namespace boost::asio;
	try {
		boost::system::error_code error;
		//sock.connect(ep, error);
		//if (error == boost::asio::error::connection_refused) {
		//	cout << "No Remote Server At: " << this->name << endl;
		//	return;
		//}
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
	sock.async_send(buffer(str, len), [](const boost::system::error_code &ec, std::size_t bytes_transferred) {});
	if (error == boost::asio::error::eof || error == boost::asio::error::shut_down || error == boost::asio::error::connection_aborted || error == boost::asio::error::connection_reset) {
		cout << "Send Data Error::" << GetLastError() << endl;
		sock.close();
		return; // Connection closed cleanly by peer.
	}
}

void Async_Server::init() {
	using namespace boost::asio;
	acceptor.accept(sock);
	//acceptor.async_accept(sock, [](const boost::system::error_code &error) {});
}

