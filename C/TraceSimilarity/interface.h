#pragma once
#ifndef __INTERFACE_H__
//#define __INTERFACE_H__
#pragma message("H")
#pragma comment(lib, "WS2_32")

#include <boost/asio.hpp>

#define RESULTPORT 15777
#define REQUESTPORT 15777
#define PARAMPORT 15778
#define IP "127.0.0.1"
#define MAX_BUFFER 2048


//template<typename _Func, typename... _Argv>
//uint64_t elapse_time(_Func && f, _Argv&&... argv);

template<typename _Func, typename... _Argv>
uint64_t elapse_time(_Func && f, _Argv&&... argv) {
	auto s = chrono::steady_clock::now();
	f(forward<_Argv>(argv)...);
	//f(argv...);
	auto interval = chrono::steady_clock::now() - s;
	return static_cast<uint64_t>(chrono::duration_cast<chrono::milliseconds>(interval).count());
}


struct Boost_Sock {
	boost::asio::io_service ioservice;
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::endpoint ep;
	std::string ip;
	unsigned short port;
	Boost_Sock(std::string ip, unsigned short port) :ip(ip), port(port), sock(ioservice), ep(boost::asio::ip::address::from_string(ip), port) {
	}
	void send_str(const char * str, size_t len);
	void msg_loop();
};


void boost_return();
void file_return();
void return_by_socket();
void paramop_return();


//char * result_encode(const struct TimeSimilarity & );
//char * result_encode(const struct TimeSimilarityList &);
//char * result_encode(const struct CoordSimilarity &);
//char * result_encode(const struct CoordSimilarityList &);

struct Boost_Sock;

#endif