#include <windows.h>
#include <string>
#include <time.h>
#include <vector>
#include <iostream>

#include "def.h"
#include "xNES.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include "interface.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp> 

using namespace std;

//#define UNICODE

vector<string> csvname;

std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[] _Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[] _Dest;
	setlocale(LC_ALL, "C");
	return result;
}

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
			if (state == 0)
				x = atof(string(cols, abuf).c_str());
			else if (state == 1)
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

void get_all_csv(string fullpath = "../../case/origin") {
	namespace fs = boost::filesystem;
	fs::path full_path(fullpath, fs::native);
	if (!fs::exists(fullpath)) {
		return;
	}
	fs::directory_iterator end_iter;
	for (fs::directory_iterator iter(fullpath); iter != end_iter; iter++) {
		try {

			if (fs::extension(*iter) == ".csv") {
				csvname.push_back(iter->path().filename().string());
				//csvname.push_back(iter->path().string());
			}
		}
		catch (const std::exception & ex) {
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}
}

CoordSimilarityList find_coord(string tracename) {
	using namespace std;
	vector<vector<Point>> tofind;
	vector<Point> trace;
	if (csvname.empty())
	{
		get_all_csv();
	}
	for (int i = 0; i < csvname.size(); i++)
	{
		if (tracename == csvname[i])
		{
			trace = read_csv(s2ws(csvname[i]));
		}
		else {
			tofind.push_back(read_csv(s2ws(csvname[i])));
		}
	}
	return CoordSort(trace, tofind);
}

TimeSimilarityList find_time(string tracename) {
	using namespace std;
	vector<vector<TPoint>> tofind;
	vector<TPoint> trace;
	if (csvname.empty())
	{
		get_all_csv();
	}
	for (int i = 0; i < csvname.size(); i++)
	{
		if (tracename == csvname[i])
		{
			trace = read_csv_time(s2ws(csvname[i]));
		}
		else {
			tofind.push_back(read_csv_time(s2ws(csvname[i])));
		}
	}
	return TimeSort(trace, tofind);
}

CoordSimilarity cmp_coord(string tracename1, string tracename2) {
	using namespace std;
	vector<Point> trace1, trace2;
	trace1 = read_csv(s2ws(tracename1));
	trace2 = read_csv(s2ws(tracename1));
	return CoordCompare(trace1, trace2);
}

TimeSimilarity cmp_time(string tracename1, string tracename2) {
	using namespace std;
	vector<TPoint> trace1, trace2;
	trace1 = read_csv_time(s2ws(tracename1));
	trace2 = read_csv_time(s2ws(tracename1));
	return TimeCompare(trace1, trace2);
}

/*
	Flow Line
	* get_all_csv
	find_coord/find_time
	result_encode(+4)
	xxx_return
*/

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	//read_csv_time(L"../../case/origin/1t.csv");

	//return_by_socket();
	vector<Point> trace_coord[4];
	for (int i = 0;i < 4;i++) {
		wstring path = L"../../case/origin/";
		path += (i + '0');
		path += L".csv";
		trace_coord[i] = read_csv(path);
	}
	//trace_coord[0] = read_csv(L"../../case/coord/1a.csv");
	//trace_coord[1] = read_csv(L"../../case/coord/1b.csv");
	//trace_coord[2] = read_csv(L"../../case/coord/2a.csv");
	//trace_coord[3] = read_csv(L"../../case/coord/2b.csv");
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < i;j++) {
			CoordSimilarity coordsimilarity = CoordCompare(trace_coord[i], trace_coord[j]);
			for (unsigned int k = 0;k < coordsimilarity.trace_sections.size();k++) {
				//cout << coordsimilarity.trace_sections[k].t1_begin << " ";
				//cout << coordsimilarity.trace_sections[k].t1_end << " ";
				//cout << coordsimilarity.trace_sections[k].t2_begin << " ";
				//cout << coordsimilarity.trace_sections[k].t2_end << endl;
			}
			cout << i << " and " << j << " ";
			printf("%.2f%%\n", coordsimilarity.two_similarity * 100);
		}
	}
	//xNES();
	//get_all_csv();
	system("pause");
	return 0;
}