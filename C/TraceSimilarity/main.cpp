#include "interface.h"
#include "def.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include "param.h"

#include <string>
#include <time.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
#include <sstream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp> 
#include <boost/algorithm/string.hpp>

using namespace std;

//#define UNICODE

vector<string> csvname;
//Boost_Sock bm(IP, REQUESTPORT, do_req, "Request Sock");
Boost_Sock bmpop(IP, PARAMPORT, paramop_coord, "Param Sock");

//#define DATASET_ROOT "c:\\datasets\\"
#define DATASET_ROOT "C:\\datasets\\"


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
	UnmapViewOfFile(buffer_void);
	CloseHandle(hmapping);
	CloseHandle(hfile);
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
				// read time
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
				// read x
				x = atof(string(cols, abuf).c_str());
			else if (state == 1)
				// read y
				y = atof(string(cols, abuf).c_str());
			// renew cols
			cols = abuf + 1;
			// renew state
			state++;
		}
		abuf++;
	}
	UnmapViewOfFile(buffer_void);
	CloseHandle(hmapping);
	CloseHandle(hfile);
	return vp;
}

vector<TPoint> read_csv_any(wstring path) {
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
			if (state == 2)
			{
				if (beheaded) {
					// read time
					tm tmtime; tmtime.tm_sec = 0; tmtime.tm_isdst = -1;
					sscanf(cols, "%04d/%02d/%02d %02d:%02d\r", &tmtime.tm_year, &tmtime.tm_mon, &tmtime.tm_mday, &tmtime.tm_hour, &tmtime.tm_min);
					tmtime.tm_year -= 1900;
					t = mktime(&tmtime);
					// add point
					vp.push_back(TPoint(x, y, t));
				}
			}
			else {
				y = atof(string(cols, abuf - 1).c_str());
				vp.push_back(TPoint(x, y, 0));
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
				// read x
				x = atof(string(cols, abuf).c_str());
			else if (state == 1)
				// read y
				y = atof(string(cols, abuf).c_str());
			// renew cols
			cols = abuf + 1;
			// renew state
			state++;
		}
		abuf++;
	}
	UnmapViewOfFile(buffer_void);
	CloseHandle(hmapping);
	CloseHandle(hfile);
	return vp;
}
//"../../case/origin"
void get_all_csv(string fullpath = DATASET_ROOT) {
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

void clean(vector<Point> &trace) {
	trace.erase(trace.begin());
}

string find_coord(string tracename) {
	using namespace std;
	vector<vector<Point>> tofind;
	vector<Point> trace;
	if (csvname.empty()) {
		get_all_csv();
	}
	for (int i = 0; i < csvname.size(); i++) {
		if (tracename == csvname[i]) {
			trace = read_csv_any(s2ws(DATASET_ROOT + csvname[i]));
		}
		else {
			tofind.push_back(read_csv_any(s2ws(DATASET_ROOT + csvname[i])));
		}
	}
	clean(trace);
	for (int i = 0;i < tofind.size();i++) {
		clean(tofind[i]);
	}
	CoordSimilarityList coord_list = CoordSort(trace, tofind);
	string res1;
	for (int i = 0;i < min(5, (int)coord_list.similarities.size());i++) {
		if (i > 0) res1 += ':';
		res1 += tracename;
		int j, k = coord_list.similarities[i].first;
		for (j = 0;j < coord_list.trace_sections.size();j++) {
			if (coord_list.trace_sections[j].index == k) break;
		}
		if (j < coord_list.trace_sections.size()) {
			res1 += '&';
			string tmp;
			stringstream ss;
			ss.clear();
			ss << coord_list.trace_sections[j].t1_begin;
			ss >> tmp;
			res1 += tmp + '!';
			ss.clear();
			ss << coord_list.trace_sections[j].t1_end - 1;
			ss >> tmp;
			res1 += tmp + '*' + csvname[k] + '&';
			ss.clear();
			ss << coord_list.trace_sections[j].t2_begin;
			ss >> tmp;
			res1 += tmp + '!';
			ss.clear();
			ss << coord_list.trace_sections[j].t2_end - 1;
			ss >> tmp;
			res1 += tmp + '*';
			ss.clear();
			ss << coord_list.similarities[i].second;
			ss >> tmp;
			res1 += tmp;
		}
	}
	return res1;
}

string find_time(string tracename) {
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
			trace = read_csv_any(s2ws(DATASET_ROOT + csvname[i]));
		}
		else {
			tofind.push_back(read_csv_any(s2ws(DATASET_ROOT + csvname[i])));
		}
	}
	clean(trace);
	for (int i = 0;i < tofind.size();i++) {
		clean(tofind[i]);
	}
	TimeSimilarityList time_list = TimeSort(trace, tofind);
	string res1;
	for (int i = 0; i < min(5, (int)time_list.similarities.size()); i++) {
		if (i > 0) res1 += ':';
		res1 += tracename;
		int j, k = time_list.similarities[i].first;
		for (j = 0; j < time_list.trace_sections.size(); j++) {
			if (time_list.trace_sections[j].index == k) break;
		}
		if (j < time_list.trace_sections.size()) {
			res1 += '&';
			string tmp;
			stringstream ss;
			ss.clear();
			ss << time_list.trace_sections[j].t1_begin;
			ss >> tmp;
			res1 += tmp + '!';
			ss.clear();
			ss << time_list.trace_sections[j].t1_end - 1;
			ss >> tmp;
			res1 += tmp + '*' + csvname[k] + '&';
			ss.clear();
			ss << time_list.trace_sections[j].t2_begin;
			ss >> tmp;
			res1 += tmp + '!';
			ss.clear();
			ss << time_list.trace_sections[j].t2_end - 1;
			ss >> tmp;
			res1 += tmp + '*';
			ss.clear();
			ss << time_list.similarities[i].second;
			ss >> tmp;
			res1 += tmp;
		}
	}
	return res1;
}

string cmp_coord(string tracename1, string tracename2) {
	using namespace std;
	vector<Point> trace1, trace2;
	trace1 = read_csv_any(s2ws(DATASET_ROOT + tracename1));
	trace2 = read_csv_any(s2ws(DATASET_ROOT + tracename2));
	clean(trace1);
	clean(trace2);
	CoordSimilarity coord_simi = CoordCompare(trace1, trace2);
	string res1 = tracename1;
	res1 += '&';
	string tmp;
	stringstream ss;
	ss.clear();
	ss << coord_simi.trace_sections[0].t1_begin;
	ss >> tmp;
	res1 += tmp + '!';
	ss.clear();
	ss << coord_simi.trace_sections[0].t1_end - 1;
	ss >> tmp;
	res1 += tmp + '*' + tracename2 + '&';
	ss.clear();
	ss << coord_simi.trace_sections[0].t2_begin;
	ss >> tmp;
	res1 += tmp + '!';
	ss.clear();
	ss << coord_simi.trace_sections[0].t2_end - 1;
	ss >> tmp;
	res1 += tmp + '*';
	ss.clear();
	ss << coord_simi.two_similarity;
	ss >> tmp;
	res1 += tmp;
	return res1;
}

string cmp_time(string tracename1, string tracename2) {
	using namespace std;
	vector<TPoint> trace1, trace2;
	trace1 = read_csv_any(s2ws(DATASET_ROOT + tracename1));
	trace2 = read_csv_any(s2ws(DATASET_ROOT + tracename2));
	clean(trace1);
	clean(trace2);
	TimeSimilarity time_simi = TimeCompare(trace1, trace2);
	string res1 = tracename1;
	res1 += '&';
	string tmp;
	stringstream ss;
	ss.clear();
	ss << time_simi.trace_sections[0].t1_begin;
	ss >> tmp;
	res1 += tmp + '!';
	ss.clear();
	ss << time_simi.trace_sections[0].t1_end - 1;
	ss >> tmp;
	res1 += tmp + '*' + tracename2 + '&';
	ss.clear();
	ss << time_simi.trace_sections[0].t2_begin;
	ss >> tmp;
	res1 += tmp + '!';
	ss.clear();
	ss << time_simi.trace_sections[0].t2_end - 1;
	ss >> tmp;
	res1 += tmp + '*';
	ss.clear();
	ss << time_simi.two_similarity;
	ss >> tmp;
	res1 += tmp;
	return res1;
}

string do_req(const char * data, size_t len) {
	//data[len] = '\0';
	using namespace boost;
	string req(data);
	vector<string> SplitVec;
	string ans;
	split(SplitVec, req, is_any_of("*"), token_compress_on);
	if (SplitVec[1] == "") {
		// list
		ans = find_coord(SplitVec[0]);
	}
	else{
		// cmp 2
		ans = cmp_coord(SplitVec[0], SplitVec[1]);
	}
	return ans;
}

void sorttest1() {
	//printf("Sort Test");
	//std::vector< std::vector<Point> > traces;
	//for (int i = 0;i < 3;i++) traces.push_back(trace_coord[i]);
	//CoordSimilarityList coordlist = CoordSort(trace_coord[3], traces);
	//for (int i = 0;i < coordlist.similarities.size();i++) {
	//	cout << coordlist.similarities[i].first << " ";
	//	printf("%.2f%%\n", coordlist.similarities[i].second * 100);
	//}
	//puts("");
	//for (int i = 0;i < coordlist.trace_sections.size();i++) {
	//	cout << "mine between ";
	//	cout << coordlist.trace_sections[i].t1_begin << " ";
	//	cout << coordlist.trace_sections[i].t1_end << " ";
	//	cout << "with trace " << coordlist.trace_sections[i].index << " between ";
	//	cout << coordlist.trace_sections[i].t2_begin << " ";
	//	cout << coordlist.trace_sections[i].t2_end << " ";
	//	printf("%.2f%%\n", coordlist.trace_sections[i].coord_sim * 100);
	//}
	//puts("");
}

void cmptest1() {
	//vector<Point> trace_coord[4];
	//vector<TPoint> trace_time[4];

	//cout << cmp_coord("1.csv", "2.csv") << endl;
}

int wmain(int argc, TCHAR* argv[], TCHAR* env[]) {
	//return_by_socket();
	//paramop_return();
	//get_all_csv();

	cmptest1();

	cout << "Ready" << endl;
	std::wstring wstr;
	if (argc == 2) {
		wstr = std::wstring(argv[1]); // ws2s(wstr).c_str()
		cout << do_req(ws2s(wstr).c_str(), 0) << endl;
	}
	else if(argc == 999){
		wstr = std::wstring(L"2.csv*3.csv"); // ws2s(wstr).c_str()
		cout << do_req(ws2s(wstr).c_str(), 0) << endl;
	}
	else {
		bmpop.async_init();
		if (bmpop.ios_thread.joinable())
			bmpop.ios_thread.join();
		//bmpop.init();
	}
	//system("pause");
	return 0;
}