#include <boost/numeric/ublas/matrix.hpp>

#include <string>
#include <time.h>
#include <vector>

#include "def.h"
#include "TimeSimilarity.h"

std::vector<Point> AsPointList(std::vector<TPoint> t) {
	std::vector<Point> c;
	c.resize(t.size());
	for (int i = 0; i < t.size(); i++)
	{
		c[i] = Point(t[i].x, t[i].y);
	}
	return c;
}

TimeSimilarity TimeCompare(std::vector<TPoint> & t1, std::vector<TPoint> & t2) {
	std::vector<Point> p1 = AsPointList(t1), p2 = AsPointList(t2);
	CoordSimilarity coorsim = CoordCompare(p1, p2, true);
	TimeSimilarity timesim;
	// typedef CoordSimilarity TimeSimilarity
	return TimeSimilarity();
}

TimeSimilarityList TimeSort(std::vector<TPoint> & t1, std::vector< std::vector<TPoint> > & tlist) {
	return TimeSimilarityList();
}