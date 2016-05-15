#pragma once

#include "def.h"
#include <vector>

struct CoordSimilarity {
	double two_similarity;
	std::vector<TwoTraceSection> trace_sections;
	std::vector<TwoTracePoint> trace_points;
};

struct CoordSimilarityList {

};

CoordSimilarity CoordCompare(std::vector<Point> t1, std::vector<Point> t2, bool timeissue = false);
CoordSimilarityList CoordSort(std::vector<Point> t1, std::vector< std::vector<Point> > tlist, bool timeissue = false);
