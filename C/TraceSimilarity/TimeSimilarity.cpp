#include <boost/numeric/ublas/matrix.hpp>

#include <string>
#include <time.h>
#include <vector>
#include <cmath>

#include "def.h"
#include "TimeSimilarity.h"

std::vector<Point> AsPointList(std::vector<TPoint> t) {
	// This function convert vector<TPoint> to vector<Point> 
	// This is deprecated for "typedef Point TPoint" is on TODO list
	std::vector<Point> c;
	c.resize(t.size());
	for (int i = 0; i < t.size(); i++)
	{
		c[i] = Point(t[i].x, t[i].y);
	}
	return c;
}

double distance(const Point & p1, const Point & p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

TimeSimilarity TimeCompare(std::vector<TPoint> & t1, std::vector<TPoint> & t2) {
	std::vector<Point> pl1 = AsPointList(t1), pl2 = AsPointList(t2);
	CoordSimilarity coorsim = CoordCompare(pl1, pl2, true);
	std::vector<double> p_diff;
	for (int i = 0; i < coorsim.trace_sections.size(); i++)
	{
		// assume [b1, e1) NOT [b1, e1]
		int b1 = coorsim.trace_sections[i].t1_begin;
		int e1 = coorsim.trace_sections[i].t1_end;
		int b2 = coorsim.trace_sections[i].t2_begin;
		int e2 = coorsim.trace_sections[i].t2_end;
		int len1 = e1 - b1, len2 = e2 - b2;
		int maxlen = len1 > len2 ? len1 : len2;
		int pi2 = b2;
		for (int pi1 = b1; pi1 < e1; pi1++)
		{
			const Point & p1 = t1[pi1];
			//bool next_time_closer = (pi2 + 1 >= e2 || abs((long long)(t1[pi1].t - t2[pi2].t)) < abs((long long)(t1[pi1].t - t2[pi2 + 1].t)) ) ? false : true;
			bool next_xy_closer = (pi2 + 1 >= e2 || distance(t1[pi1], t2[pi2]) < distance(t1[pi1], t2[pi2 + 1])) ? false : true;
		}
	}
	TimeSimilarity timesim;
	// typedef CoordSimilarity TimeSimilarity
	return TimeSimilarity();
}

TimeSimilarityList TimeSort(std::vector<TPoint> & t1, std::vector< std::vector<TPoint> > & tlist) {
	return TimeSimilarityList();
}