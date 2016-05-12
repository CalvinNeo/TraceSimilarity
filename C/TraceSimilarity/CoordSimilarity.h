#pragma once

#include "def.h"
#include <windows.h>
#include <vector>

struct CoordSimilarity {

};

CoordSimilarity CoordCompare(std::vector<Point> t1, std::vector<Point> t2);
CoordSimilarity CoordList(std::vector<Point> t1, std::vector< std::vector<Point> > tlist);