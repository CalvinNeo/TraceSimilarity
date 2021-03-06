#pragma once
#ifndef __INTERFACE_H__
//#define __INTERFACE_H__
#pragma message("H")
#pragma comment(lib, "WS2_32")

#include <boost/asio.hpp>
#include <thread>

#define REQUESTPORT 15777
#define PARAMPORT 15778
#define IP "127.0.0.1"
#define MAX_BUFFER 8192

struct paramop_msg {
	char op[256];
	paramop_msg() {
		memset(op, '\0', 256); 
	}
};

typedef std::function<bool(struct Sync_Sock *, char *, size_t)> MSGHANDLER;
typedef std::function<void(struct Async_Sock *, char *, size_t)> AMSGHANDLER;
extern boost::asio::io_service ioservice;

template<typename _Func, typename... _Argv>
uint64_t elapse_time(_Func && f, _Argv&&... argv) {
	auto s = chrono::steady_clock::now();
	f(forward<_Argv>(argv)...);
	//f(argv...);
	auto interval = chrono::steady_clock::now() - s;
	return static_cast<uint64_t>(chrono::duration_cast<chrono::milliseconds>(interval).count());
}

//typedef void(*MSGHANDLER)(char * buffer, size_t len);

struct Sync_Sock {
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::endpoint ep;
	std::string ip;
	std::string name;
	unsigned short port;
	size_t max_buffer;
	MSGHANDLER handler;
	std::thread ios_thread;
	boost::asio::ip::tcp::acceptor acceptor;
	Sync_Sock(std::string ip, unsigned short port, MSGHANDLER msghandler = nullptr, std::string name = "") :ip(ip), port(port), sock(ioservice)
		, ep(boost::asio::ip::address::from_string(ip), port), handler(msghandler), name(name), acceptor(ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
	}
	~Sync_Sock() {
		if(ios_thread.joinable())
			ios_thread.join();
	}
	void send_str(const char * str, size_t len);
	void init();
	void async_init();
	void msg_loop();
protected:
	char ReceiveBuffer[MAX_BUFFER];
};

struct Sync_Server:public Sync_Sock {
	Sync_Server(std::string ip, unsigned short port, MSGHANDLER msghandler = nullptr, std::string name = "") :Sync_Sock(ip, port, msghandler, name) {
	}
	void init();
	void async_init(std::function<void(const boost::system::error_code &)>);
};

struct Async_Sock {
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::endpoint ep;
	std::string ip;
	std::string name;
	unsigned short port;
	size_t max_buffer;
	AMSGHANDLER handler;
	boost::asio::ip::tcp::acceptor acceptor;
	Async_Sock(std::string ip, unsigned short port, AMSGHANDLER msghandler = nullptr, std::string name = "") :ip(ip), port(port), sock(ioservice)
		, ep(boost::asio::ip::address::from_string(ip), port), handler(msghandler), name(name), acceptor(ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
		ioservice.run();
	}
	void send_str(const char * str, size_t len);
	void msg_loop();
protected:
	char ReceiveBuffer[MAX_BUFFER];
};

struct Async_Server :public Async_Sock {
	Async_Server(std::string ip, unsigned short port, AMSGHANDLER msghandler = nullptr, std::string name = "") :Async_Sock(ip, port, msghandler, name) {
		ioservice.run();
	}
	void init();
};

//#define Boost_Sock Async_Sock
//#define Boost_Server Async_Server

//typedef Async_Sock Boost_Sock;
//typedef Async_Server Boost_Server;

//typedef Sync_Sock Boost_Sock;
//typedef Sync_Server Boost_Server;

using Boost_Sock = Sync_Sock;
using Boost_Server = Sync_Server;

#endif