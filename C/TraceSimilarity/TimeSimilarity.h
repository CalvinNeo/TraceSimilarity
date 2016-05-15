#pragma once

#include "def.h"
#include <vector>

struct TimeSimilarity {
	double two_similarity;
	std::vector<TwoTraceSection> trace_sections;
	std::vector<TwoTracePoint> trace_points;
};

struct TimeSimilarityList {

};

TimeSimilarity TimeCompare(std::vector<TPoint> t1, std::vector<TPoint> t2);
TimeSimilarityList TimeSort(std::vector<TPoint> t1, std::vector< std::vector<TPoint> > tlist);