#pragma once
#ifndef __INTERFACE_H__
//#define __INTERFACE_H__
#pragma message("H")
#pragma comment(lib, "WS2_32")

#include <boost/asio.hpp>

//#define RESULTPORT 15777
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

template<typename _Func, typename... _Argv>
uint64_t elapse_time(_Func && f, _Argv&&... argv) {
	auto s = chrono::steady_clock::now();
	f(forward<_Argv>(argv)...);
	//f(argv...);
	auto interval = chrono::steady_clock::now() - s;
	return static_cast<uint64_t>(chrono::duration_cast<chrono::milliseconds>(interval).count());
}

//typedef void(*MSGHANDLER)(char * buffer, size_t len);
typedef std::function<void(char *, size_t)> MSGHANDLER;
extern boost::asio::io_service ioservice;

struct Boost_Sock {
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::endpoint ep;
	std::string ip;
	std::string name;
	unsigned short port;
	size_t max_buffer;
	MSGHANDLER handler;
	Boost_Sock(std::string ip, unsigned short port, MSGHANDLER msghandler = nullptr, std::string name = "") :ip(ip), port(port), sock(ioservice)
		, ep(boost::asio::ip::address::from_string(ip), port), handler(msghandler), name(name){
	}
	void send_str(const char * str, size_t len);
	void msg_loop();
private:
	char ReceiveBuffer[MAX_BUFFER];
};


void boost_return();
void file_return();
void return_by_socket();


//char * result_encode(const struct TimeSimilarity & );
//char * result_encode(const struct TimeSimilarityList &);
//char * result_encode(const struct CoordSimilarity &);
//char * result_encode(const struct CoordSimilarityList &);

struct Boost_Sock;

#endif