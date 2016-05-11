#include <windows.h>
#include <string>
#include <time.h>
#include <vector>

#include "def.h"
#include "read.h"
#include "xNES.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp> 

using namespace std;

#define UNICODE

vector<Point> read_csv(wstring path) {
	int record_count = 0;
	HANDLE hfile = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
	DWORD dwFileSize = GetFileSize(hfile, NULL);
	HANDLE hmapping = CreateFileMapping(hfile, 0, PAGE_READONLY, 0, 0, 0);
	LPVOID buffer_void = MapViewOfFile(hmapping, FILE_MAP_READ, 0, 0, 0);
	// Attetion to that not all csv are UNICODE, in our case, they are ANSI
	PCHAR abuf = (PCHAR)buffer_void;
	//setlocale(LC_ALL, "");

	vector<Point> vp;
	PCHAR rows = abuf, cols = abuf;
	bool beheaded = false;
	double x = 0, y = 0;
	for (DWORD offset = 0; offset < dwFileSize; offset++)
	{
		if (*abuf == '\r') {

		}
		else if (*abuf == '\n') {
			if (beheaded) {
				y = atof(string(cols, abuf - 1).c_str());
				// add point
				vp.push_back(Point(x, y));
			}
			// renew rows and cols
			rows = abuf + 1;
			cols = abuf + 1;
			beheaded = true;
		}
		else if (beheaded && *abuf == ',') {
			x = atof(string(cols, abuf).c_str());
			// renew cols
			cols = abuf + 1;
		}
		abuf++;
	}
	return vp;
}


vector<TPoint> read_csv_time(wstring path) {
	int record_count = 0;
	HANDLE hfile = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
	DWORD dwFileSize = GetFileSize(hfile, NULL);
	HANDLE hmapping = CreateFileMapping(hfile, 0, PAGE_READONLY, 0, 0, 0);
	LPVOID buffer_void = MapViewOfFile(hmapping, FILE_MAP_READ, 0, 0, 0);
	// Attetion to that not all csv are UNICODE, in our case, they are ANSI
	PCHAR abuf = (PCHAR)buffer_void;

	vector<TPoint> vp;
	PCHAR rows = abuf, cols = abuf;
	bool beheaded = false;
	double x = 0, y = 0;
	unsigned long long t = 0;
	int state = 0;
	for (DWORD offset = 0; offset < dwFileSize; offset++)
	{
		if (*abuf == '\r') {

		}
		else if (*abuf == '\n') {
			if (beheaded) {
				tm tmtime; tmtime.tm_sec = 0; tmtime.tm_isdst = -1;
				sscanf(cols, "%04d/%02d/%02d %02d:%02d\r", &tmtime.tm_year, &tmtime.tm_mon, &tmtime.tm_mday, &tmtime.tm_hour, &tmtime.tm_min);
				tmtime.tm_year -= 1900;
				t = mktime(&tmtime);
				// add point
				vp.push_back(TPoint(x, y, t));
			}
			// renew rows and cols
			rows = abuf + 1;
			cols = abuf + 1;
			// renew state
			state = 0;
			beheaded = true;
		}
		else if (beheaded && *abuf == ',') {
			if(state == 0)
				x = atof(string(cols, abuf).c_str());
			else if(state == 1)
				y = atof(string(cols, abuf).c_str());
			// renew cols
			cols = abuf + 1;
			// renew state
			state++;
		}
		abuf++;
	}
	return vp;
}

void get_all_csv() {
	namespace fs = boost::filesystem;
	string fullpath = ".";
	fs::path full_path(fullpath, fs::native);
	if (!fs::exists(fullpath)) {
		return; 
	}
	fs::directory_iterator end_iter;
	for (fs::directory_iterator iter(fullpath); iter != end_iter; iter++) {
		try {
			
			if (fs::extension(*iter) == ".csv") {
				std::cout << *iter << " is a file" << std::endl;
			}
		}
		catch (const std::exception & ex) {
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}
}

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	//read_csv_time(L"F:\\Codes\\C++\\TraceSimilarity\\case\\origin\\1t.csv");
	//xNES();
	get_all_csv();
	system("pause");
	return 0;
}