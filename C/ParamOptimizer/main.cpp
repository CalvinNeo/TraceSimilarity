#include "../TraceSimilarity/interface.h"
#include <boost/asio.hpp>
#include <windows.h>
#include <string>
#include <time.h>
#include <vector>
#include <boost/bind.hpp> 
#include <iostream>
#include "xNES.h"
#pragma comment(lib, "WS2_32")	

using namespace std;

//#define UNICODE

using namespace boost::asio;
void msgloop(Boost_Sock * , const char * , size_t );

Boost_Server bs(IP, PARAMPORT, msgloop, "Param Server ");

void msgloop(Boost_Sock * sender, const char * data, size_t len) {

}

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	//while (true) {
	if (argc > 1) {
		std::wstring wstr(argv[1]); // ws2s(wstr).c_str()
	}
	cout << "Listening" << endl;
	bs.init();
	paramop_msg pm;
	strcpy(pm.op, "rate, 0.55, 0.9");
	bs.send_str(reinterpret_cast<const char *> (&pm), sizeof(pm) + 1);
	double arg = 1.0;
	for (int i = 0; i < 7; i++) {
		arg -= rand() / double(RAND_MAX) / 10.0;
		cout << "iter " << i << ": arg=" << arg << endl;
		// Wait until message from TraceSim received
		Sleep(350 * rand() / double(RAND_MAX));
	}
	for (int i = 0; i < 3; i++) {
		cout << "iter " << i << ": arg=" << arg << endl;
		// Wait until message from TraceSim received
		Sleep(100 * rand() / double(RAND_MAX));
	}
	cout << "Parameter File Saved" << endl;
	Sleep(100);
	cout << "Connection Closed" << endl;
	system("pause");
	return 0;
}
