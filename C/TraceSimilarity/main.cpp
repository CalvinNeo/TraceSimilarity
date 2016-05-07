#include <windows.h>
#include <string>
#include <time.h>
#include <vector>

#include "def.h"
#include "read.h"
#include "xNES.h"

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

void q_par(int * arr, int start, int end) {
	if (start >= end) return;
	int i = start, j = end ;
	while (i < j)
	{
		while (i < j && arr[i] > arr[end]) i++;
		while (i < j && arr[j] <= arr[end]) j--;
		swap(arr[i], arr[j]);
	}
	//if (arr[i] <= arr[end])//防止本来就是有序的
	//{
	//	swap(arr[i], arr[end]);
	//}
	//else
	//	i++;
	swap(arr[i], arr[end]);
	q_par(arr, start, i - 1);
	q_par(arr, i + 1, end);
}
void testqsort() {
	//int arr[] = { 3,4,2,8,0,2,1 };
	//int arr[] = { 1,2,3,4,5,6,7 };
	int arr[] = { 7,6,5,4,3,2,1 };
	q_par(arr, 0, 6);
	for (int i = 0; i < 7; i++)
	{
		cout << arr[i] << " ";
	}
}
void m_par(int * arr, int * res, int start, int end) {
	if (start >= end) return;
	int len = end - start + 1;
	int mid = start + len / 2;
	m_par(arr, res, start, mid);
	m_par(arr, res, mid + 1, end);
	int i = start, j = mid + 1;


}
void testmsort() {
	//int arr[] = { 3,4,2,8,0,2,1 };
	//int arr[] = { 1,2,3,4,5,6,7 };
	int arr[] = { 7,6,5,4,3,2,1 };
	int res[7];
	m_par(arr, res, 0, 6);
	for (int i = 0; i < 7; i++)
	{
		cout << res[i] << " ";
	}

}
int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	//read_csv_time(L"F:\\Codes\\C++\\TraceSimilarity\\case\\origin\\1t.csv");
	//xNES();
	testmsort();
	system("pause");
	return 0;
}