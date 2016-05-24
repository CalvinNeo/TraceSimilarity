#pragma once

#include <map>

struct Point {
	double x; //longitude
	double y; //latitude
	Point() = default;
	Point(double x, double y) : x(x), y(y) {

	};
};

struct TPoint : public Point{
	unsigned long long t; //timestamp
	TPoint() = default;
	TPoint(double x, double y, unsigned long long timestamp) : Point(x, y), t(timestamp) {

	};
};

struct TwoTraceSection {
	int t1_begin, t1_end, t2_begin, t2_end;
	double coord_sim, time_sim;
	TwoTraceSection(int l1, int r1, int l2, int r2) : t1_begin(l1), t1_end(r1), t2_begin(l2), t2_end(r2), coord_sim(0.0), time_sim(0.0) {

	};
	TwoTraceSection(int l1, int r1, int l2, int r2, double c_sim) : t1_begin(l1), t1_end(r1), t2_begin(l2), t2_end(r2), coord_sim(c_sim), time_sim(0.0) {

	};
	TwoTraceSection(int l1, int r1, int l2, int r2, double c_sim, double t_sim) : t1_begin(l1), t1_end(r1), t2_begin(l2), t2_end(r2), coord_sim(c_sim), time_sim(t_sim) {

	};
};

struct TraceSection {
	int index;
	int t1_begin, t1_end, t2_begin, t2_end;
	double coord_sim, time_sim;
	TraceSection(int index, TwoTraceSection tt) :index(index), t1_begin(tt.t1_begin), t1_end(tt.t1_end), t2_begin(tt.t2_begin), t2_end(tt.t2_end), coord_sim(tt.coord_sim), time_sim(tt.time_sim) {

	}
};

// 这个结构可以直接使用pair<int, int> 代替
typedef std::pair<int, int> TwoTracePoint;
//struct TwoTracePoint {
//	int i1, i2;
//	TwoTracePoint(int i1, int i2) : i1(i1), i2(i2) {
//
//	};
//};

typedef std::pair<int, double> kth_similarity;