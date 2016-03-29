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