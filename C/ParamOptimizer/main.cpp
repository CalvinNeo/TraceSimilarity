#include "../TraceSimilarity/interface.h"
#include <boost/asio.hpp>
#include <windows.h>
#include <string>
#include <time.h>
#include <vector>
#include <boost/bind.hpp> 
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "xNES.h"
#pragma comment(lib, "WS2_32")	

using namespace std;

//#define UNICODE

using namespace boost::asio;
void msgloop(Boost_Sock * , const char * , size_t );

Boost_Server bs(IP, PARAMPORT, msgloop, "Param Server ");

void msgloop(Boost_Sock * sender, const char * data, size_t len) {
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
	cout << "Parameter Saved" << endl;
	if (strcmp(data, "done")==0) {
		paramop_msg pm;
		strcpy(pm.op, "end"); 
		bs.send_str(reinterpret_cast<const char *> (&pm), sizeof(pm) + 1);
	}
}
//std::function<void(const boost::system::error_code &)>
void accept_handler(const boost::system::error_code & error) {
	if (error == 0) {
		paramop_msg pm;
		strcpy(pm.op, "start");
		bs.send_str(reinterpret_cast<const char *> (&pm), sizeof(pm) + 1);
	}
	else {
		printf("Error\n");
	}
}

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	if (argc > 1) {
		std::wstring wstr(argv[1]); // ws2s(wstr).c_str()
	}
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	// optimize value start range, search in [start - range / 2, start + range / 2]
	TCHAR cmdline[] = TEXT("TraceSimilarity.exe a 1.0 1.0");
	cout << "Listening" << endl;
	bs.async_init(accept_handler);
	//bs.init();
	//BOOL bRet = CreateProcess(NULL, cmdline, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	//if (bRet) {
	//	WaitForSingleObject(pi.hProcess, INFINITE);
	//}
	cout << "Connection Closed" << endl;
	//system("pause");
	if (bs.ios_thread.joinable())
		bs.ios_thread.join();
	//while (true) {
	//	Sleep(1);
	//}

	//using namespace boost::asio;
	//steady_timer timer1{ ioservice, std::chrono::seconds{ 1 } };
	//timer1.async_wait([](const boost::system::error_code &ec)
	//{ std::cout << "1 sec\n"; });

	//steady_timer timer2{ ioservice, std::chrono::seconds{ 3 } };
	//timer2.async_wait([](const boost::system::error_code &ec)
	//{ std::cout << "3 sec\n"; });

	//std::thread thread1{ []() { ioservice.run(); } };
	//std::thread thread2{ []() { ioservice.run(); } };
	//thread1.join();
	//thread2.join();

	return 0;
}
