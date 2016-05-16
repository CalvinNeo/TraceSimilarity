#pragma once

#include "def.h"
#include <vector>
#include "CoordSimilarity.h"

struct TimeSimilarity {
	double two_similarity;
	std::vector<TwoTraceSection> trace_sections;
	std::vector<TwoTracePoint> trace_points;
};
//typedef CoordSimilarity TimeSimilarity;

struct TimeSimilarityList {

};

TimeSimilarity TimeCompare(std::vector<TPoint> & t1, std::vector<TPoint> & t2);
TimeSimilarityList TimeSort(std::vector<TPoint> & t1, std::vector< std::vector<TPoint> > & tlist);