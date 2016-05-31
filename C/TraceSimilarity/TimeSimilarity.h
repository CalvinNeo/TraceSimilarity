#pragma once

#include "def.h"
#include <vector>
#include "CoordSimilarity.h"

struct TimeSimilarity {
	double two_similarity;
	std::vector<TwoTraceSection> trace_sections;
};

struct TimeSimilarityList {
	std::vector<kth_similarity> similarities;
	std::vector<TraceSection> trace_sections;
};

TimeSimilarity TimeCompare(std::vector<TPoint> & t1, std::vector<TPoint> & t2);
TimeSimilarityList TimeSort(std::vector<TPoint> & t1, std::vector< std::vector<TPoint> > & tlist);