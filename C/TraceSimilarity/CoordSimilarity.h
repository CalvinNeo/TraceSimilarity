#pragma once

#include "def.h"
#include <windows.h>
#include <vector>

struct CoordSimilarity {
	double similarity_2;
};

CoordSimilarity CoordCompare(std::vector<Point> t1, std::vector<Point> t2);
CoordSimilarity CoordList(std::vector<Point> t1, std::vector< std::vector<Point> > tlist);
double Cal(double** ca, int i, int j);
double dis(int i, int j);
inline double min3(double f1, double f2, double f3);
