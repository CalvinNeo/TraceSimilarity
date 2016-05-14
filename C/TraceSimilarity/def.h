#pragma once

struct Point {
	double x; //longitude
	double y; //latitude
	Point(double x, double y) : x(x), y(y) {

	};
};

struct TPoint : public Point{
	double t; //timestamp
	TPoint(double x, double y, unsigned long long timestamp) : Point(x, y), t(timestamp) {

	};
};

struct TwoTraceSection {
	int t1_begin, t1_end, t2_begin, t2_end;
	TwoTraceSection(int l1, int r1, int l2, int r2) : t1_begin(l1), t1_end(r1), t2_begin(l2), t2_end(r2) {

	};
};

struct TwoTracePoint {
	int i1, i2;
	TwoTracePoint(int i1, int i2) : i1(i1), i2(i2) {

	};
};

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
