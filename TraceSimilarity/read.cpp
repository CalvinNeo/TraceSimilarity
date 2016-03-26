#include <windows.h>
#include <string>

using namespace std;

int read_csv(string path) {
	int err = 0;
	HANDLE hfile = CreateFile(L"F:\\Codes\\C++\\", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
	HANDLE hmapping = CreateFileMapping(hfile, 0, PAGE_READONLY, 0, 0, 0);
	LPVOID buffer_void = MapViewOfFile(hmapping, FILE_MAP_READ, 0, 0, 0);

}