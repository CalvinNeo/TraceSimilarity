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
		cout << "Listening" << endl;
		bs.init();
		paramop_msg pm;
		strcpy(pm.op, "rate, 0.55, 0.9");
		bs.send_str(reinterpret_cast<const char *> (&pm), sizeof(pm) + 1);
		cout << "Connection End" << endl;
	//}
	system("pause");
	return 0;
}
