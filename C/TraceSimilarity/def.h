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
