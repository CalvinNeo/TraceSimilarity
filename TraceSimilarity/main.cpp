#include <windows.h>
#include <string>
#include "read.h"

using namespace std;

#define UNICODE

int read_csv(wstring path) {
	int record_count = 0;
	HANDLE hfile = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
	HANDLE hmapping = CreateFileMapping(hfile, 0, PAGE_READONLY, 0, 0, 0);
	LPVOID buffer_void = MapViewOfFile(hmapping, FILE_MAP_READ, 0, 0, 0);
	PWCHAR wbuf = (PWCHAR)buffer_void;
	size_t wlen = wcslen(wbuf);
	setlocale(LC_ALL, "");
	//printf("%s", wbuf);
	PWCHAR wbuf2 = L"123";
	wstring ws(wbuf2);

	wcout << ws << endl;

	
	return record_count;
}


int read_csv_time(wstring path) {
	int record_count = 0;
	HANDLE hfile = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
	HANDLE hmapping = CreateFileMapping(hfile, 0, PAGE_READONLY, 0, 0, 0);
	LPVOID buffer_void = MapViewOfFile(hmapping, FILE_MAP_READ, 0, 0, 0);

	return record_count;
}

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	read_csv(L"F:\\Codes\\C++\\TraceSimilarity\\TraceSimilarity\\0.csv");
	return 0;
}