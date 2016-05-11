#pragma once

#include "def.h"
#include <vector>

struct TimeSimilarity {

};

TimeSimilarity TimeCompare(std::vector<TPoint> t1, std::vector<TPoint> t2);
TimeSimilarity TimeList(std::vector<TPoint> t1, std::vector< std::vector<TPoint> > tlist);